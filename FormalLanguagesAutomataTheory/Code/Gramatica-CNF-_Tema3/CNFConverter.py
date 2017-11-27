from collections import defaultdict
from copy import deepcopy
from copy import copy
from itertools import combinations
from itertools import chain
from types import MethodType

NULL = '_'

class ProductionDict:
    def __init__(self):
        self.productions = defaultdict(list)

    def addProduction(self, key, prod):
        toAdd = prod if len(prod) > 0 else [NULL]
        if toAdd not in self.productions[key]:
            self.productions[key].append(toAdd)

    def removeProduction(self, key, prod):
        self.productions[key].remove(prod)

    def items(self):
        return self.productions.items()

    def values(self):
        return self.productions.values()

    def __getitem__(self, key):
        return self.productions[key]

    def __len__(self):
        return len(self.productions)

    def remove(self, key):
        self.productions.remove(key)

class Grammar:
    def __init__(self):
        self.N = set()                  # Nonterminals set
        self.T = set()                  # Terminals set
        self.P = ProductionDict()       # Productions
        self.S = None                   # Start simbol

    def updateNonterminals(self, items):    # Expects an iterable
        self.N.update(items)

    def updateTerminals(self, items):       # Expects an iterable
        self.T.update(items)

    # Expects: lhs - character, Nonterminal
    #          rhs - string, Terminals and Nonterminals
    def addProduction(self, lhs, rhs):
        # self.P[lhs].append(rhs)
        self.P.addProduction(lhs, rhs)

    def setStartingSymbol(self, start):     # Expects a character, Nonterminal
        self.S = start

    def show(self):
        print(self.N)
        print(self.T)
        # print(self.P)
        for (k, v) in self.P.items():
            print(k, v)
        print(self.S)

symbolPool = set()
gen = 0;

def symbolPoolRefill():
    global symbolPool
    global gen
    for c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
        symbolPool.add(c if gen == 0 else c + str(gen))
    gen += 1

def getNewSymbol():
    global symbolPool
    newSym = None
    try:
        newSym = symbolPool.pop()
    except KeyError:
        symbolPoolRefill()
        newSym = symbolPool.pop()
    return newSym

def unionProducts(prods1, prods2):
    newProds = ProductionDict()
    for (k, v) in prods1.items():
        for p in v:
            newProds.addProduction(k, p)
    for (k, v) in prods2.items():
        for p in v:
            newProds.addProduction(k, p)
    return newProds

# If grammar g contains a production in which the start symbol appears
# on the right hand side, creates a new tart symbol S1 and adds the
# production S1 -> S
def doNoRhsStart(g):
    for (lhs, rhs) in g.P.items():
        for prodEl in rhs:
            if(g.S in prodEl):
                S1 = g.S + '0'
                g.updateNonterminals([S1])
                g.addProduction(S1, [g.S])
                g.setStartingSymbol(S1)
                return

# Returns a set of nonterminals whitch are going to NULL
# Excepting S
def getNullProductingNonterminals(g):
    nonterminals = set()
    for (lhs, rhs) in g.P.items():
        if [NULL] in rhs:
            nonterminals.add(lhs)
    return nonterminals

def removeNullProductions(g):
    while True:
        nullables = getNullProductingNonterminals(g)
        if len(nullables) == 0 or (len(nullables) == 1 and g.S in nullables):
            break

        newProds = ProductionDict()
        for (lhs, rhs) in g.P.items():
            for singleProduction in rhs:
                if singleProduction != [NULL]:
                    symbolsSet = set(singleProduction)
                    if len(nullables & symbolsSet) == 0:   # if current production doesn't have nullable symbols
                        newProds.addProduction(lhs, singleProduction)
                    else:
                        simpleNewProds = [v for (k, v) in enumerate(singleProduction) if v not in nullables or len(g.P[v]) > 1]
                        newProds.addProduction(lhs, simpleNewProds)
                        indices = [k for (k, v) in enumerate(singleProduction) if v in nullables and len(g.P[v]) > 1]
                        if(len(indices) > 0):
                            for i in range(0, len(indices) + 1):
                                for combination in combinations(indices, i):
                                    newProd = [v for (k, v) in enumerate(singleProduction) if k not in combination and not (v in nullables and len(g.P[v]) == 1)]
                                    newProds.addProduction(lhs, newProd)
                elif lhs == g.S:
                    newProds.addProduction(lhs, singleProduction)
                elif lhs in nullables and lhs in g.N and len(rhs) == 1:
                    g.N.remove(lhs)
        g.P = newProds

def getUnitProductions(g):
    unitProductions = ProductionDict()
    for (start, prods) in g.P.items():
        for prod in prods:
            if len(prod) == 1 and prod[0] in g.N:
                unitProductions.addProduction(start, prod)
    return unitProductions

def removeUnitProductions(g):
    unitProductions = getUnitProductions(g)

    while len(unitProductions) > 0:
        for (t, prod) in unitProductions.items():
            # print("unit: " + t + str(prod))
            s = prod[0][0]
            for sProd in g.P[s]:
                g.P.addProduction(t, sProd)
            g.P.removeProduction(t, prod[0])

            # print("verific pentru " + s)

            if not (s in [x for sublist in unitProductions.values() for item in sublist for x in item]):
                # the element doesn't appears on the right side of another production
                # print("scot " + s)
                g.P.remove(s)
                g.N.remove(s)
        unitProductions = getUnitProductions(g)

def removeLongProductions(g):
    newProds = ProductionDict()
    for (start, prods) in g.P.items():
        for prod in prods:
            if len(prod) > 2:
                crtProd = deepcopy(prod)
                crtSym = start
                while True:
                    keepSymbol = crtProd[0]
                    crtProd.pop(0)
                    tmpSym = None
                    if len(crtProd) == 2:
                        union = unionProducts(g.P, newProds)
                        # union = newProds
                        for (k, v) in union.items():
                            if len(v) == 1 and v[0] == crtProd:
                                tmpSym = k
                                break

                    if tmpSym == None:
                        tmpSym = getNewSymbol()
                        g.N.add(tmpSym)

                    newProd = [keepSymbol, tmpSym]
                    newProds.addProduction(crtSym, newProd)
                    crtSym = tmpSym

                    if len(crtProd) == 2:
                        newProds.addProduction(crtSym, crtProd)
                        break
            else:
                newProds.addProduction(start, prod)
    g.P = newProds

def removeMixedProductions(g):
    newProds = ProductionDict()
    for (start, prods) in g.P.items():
        for prod in prods:
            # print prod
            # print(((prod[0] in g.T and prod[1] in g.N) or (prod[0] in g.N and prod[1] in g.T)))
            if len(prod) == 2 and ((prod[0] in g.T and prod[1] in g.N) or (prod[0] in g.N and prod[1] in g.T)):
                crtProd = deepcopy(prod)
                if crtProd[0] in g.T:
                    union = unionProducts(newProds, g.P)
                    # union = newProds
                    for (k, v) in union.items():
                        newSym = None
                        if len(v) == 1 and len(v[0]) == 1 and v[0][0] == crtProd[0]:
                            newSym = k
                            # print ("am gasit un simbol de refolosit")
                            # print(str(v) + " " + " " + str(v[0]) + " " + v[0][0])
                            break
                    if newSym is None:
                        newSym = getNewSymbol()
                        # print("am scos din pool " + newSym)
                        g.N.update([newSym])
                    newProds.addProduction(newSym, [crtProd[0]])
                    # print("sunt la pasul " + start + " -> " + str(prod))
                    # print("am aduagat: " + newSym + "->" + str([crtProd[0]]))
                    crtProd[0] = newSym
                if crtProd[1] in g.T:
                    union = unionProducts(newProds, g.P)
                    # union = newProds
                    for (k, v) in union.items():
                        newSym = None
                        if len(v) == 1 and len(v[0]) == 1 and v[0][0] == crtProd[1]:
                            newSym = k
                            break
                    if newSym is None:
                        newSym = getNewSymbol()
                        g.N.update([newSym])
                    newProds.addProduction(newSym, [crtProd[1]])
                    # print("sunt la pasul " + start + " -> " + str(prod))
                    # print("am aduagat: " + newSym + "->" + str([crtProd[1]]))
                    crtProd[1] = newSym
                newProds.addProduction(start, crtProd)
                # print("am aduagat la final: " + start + "->" + str(prod))
            else:
                newProds.addProduction(start, prod)
                # print("am aduagat la final: " + str(prod))
    g.P = newProds

# function to convert a grammar to CNF
# parameter g the grammar to be converted
# return a new grammar in CNF
def CNFConverter(g):
    cnf = deepcopy(g)
    # converter algorithm

    # Step 1: if the start symbol S appears on the right hand side of a
    # production, add a new start symbol S1 and the production S -> S1
    doNoRhsStart(cnf)
    # cnf.show()
    # Step 2: remove null productions
    removeNullProductions(cnf)
    # cnf.show()
    # Step 3: remove unit productions
    removeUnitProductions(cnf)
    # cnf.show()
    # Step 4: remove long productions
    removeLongProductions(cnf)
    # cnf.show()
    # Step 5: remove mixed productions
    # removeMixedProductions(cnf)
    # cnf.show()

    return cnf

def classExample():
    cfg = Grammar()
    cfg.updateNonterminals(["S", "B", "D", "F", "G", "H"])
    symbolPool.discard("S")
    symbolPool.discard("B")
    symbolPool.discard("D")
    symbolPool.discard("F")
    symbolPool.discard("G")
    symbolPool.discard("H")
    symbolPool.discard("R")
    cfg.updateTerminals(['a', 'b', 'c', 'e', 'd', 'g', NULL])
    cfg.addProduction('S', ["a", "B", 'c', 'D', 'e', 'F'])
    cfg.addProduction('S', ["H", "F"])
    cfg.addProduction('S', ["H", "B", 'c'])
    cfg.addProduction('B', ['b'])
    cfg.addProduction('B', [NULL])
    cfg.addProduction('D', ['d'])
    cfg.addProduction('D', [NULL])
    cfg.addProduction('F', ['G'])
    cfg.addProduction('G', ['g'])
    cfg.addProduction('H', [NULL])
    cfg.setStartingSymbol('S')

    cfg.show()

    cnf = CNFConverter(cfg)

    cnf.show()

def exemplu():
    cfg = Grammar()
    cfg.updateNonterminals(['S', 'A', 'B'])
    symbolPool.discard("S")
    symbolPool.discard("A")
    symbolPool.discard("B")
    cfg.updateTerminals(["a", "b", NULL])
    cfg.updateTerminals(['a', 'b'])
    cfg.setStartingSymbol('S')
    cfg.addProduction('S', ['A', 'S', 'A'])
    cfg.addProduction('S', ['a', 'B'])
    cfg.addProduction('A', ['B'])
    cfg.addProduction('A', ['S'])
    cfg.addProduction('B', ['b'])
    cfg.addProduction('B', [NULL])

    cnf = CNFConverter(cfg)
    cnf.show()

def exemplu2():
    cfg = Grammar()
    cfg.updateNonterminals(['S', 'X', 'Y'])
    symbolPool.discard("S")
    symbolPool.discard("X")
    symbolPool.discard("Y")
    cfg.updateTerminals(["a", "b", "c", NULL])
    cfg.setStartingSymbol('S')
    cfg.addProduction('S', ['a', 'X', 'b', 'X'])
    cfg.addProduction('X', ['a', 'Y'])
    cfg.addProduction('X', ['b', 'Y'])
    cfg.addProduction('X', [NULL])
    cfg.addProduction('Y', ['X'])
    cfg.addProduction('Y', ['c'])

    cnf = CNFConverter(cfg)
    cnf.show()


def main():
    symbolPoolRefill()
    # classExample()
    exemplu2()


if __name__ == '__main__':
    main()
