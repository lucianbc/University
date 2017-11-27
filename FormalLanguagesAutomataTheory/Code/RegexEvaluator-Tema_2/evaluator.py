from collections import deque
import copy


class Automaton:
    def __init__(self):
        self.Q = set()      # internal states set
        self.E = set()      # automaton alphabet; an underscore (_) is used for
                            # the empty character
        self.F = set()      # final states
        self.q0 = None      # initial states
        self.d = {}         # tranzition set
                            # tranzition format: key: (start_tag, command)
                            #                    value: { destination states }
                            # example: {(0, 'a'): {0, 1}, (0, '_'): {2}}

    def show(self):
        print("States: " + self.Q.__str__())
        print("Alphabet: " + self.E.__str__())
        print("Final States: " + self.F.__str__())
        print("Initial State: " + self.q0.__str__())
        print("Tranzitions: ")
        print(self.d)

    def lambda_closure(self, q):
        states = set()
        states.add(q)
        queue = deque()
        queue.extend(states)
        while len(queue):
            s = queue.popleft()
            not_added = self.d[(s, '_')].difference(states) if (s, '_') in self.d.keys() else {}
            queue.extend(not_added)
            states.update(not_added)
        return states

    def addTranzition(self, start, command, finish):
        if (start, command) in self.d.keys():
            self.d[(start, command)].update([finish])
        else:
            self.d.update({(start, command): { finish }})

    # for testing purpose, prints all possible lambda closures
    def check_closure(self):
        for s in self.Q:
            print(self.lambda_closure)

    def evaluate(self, word):
        states = set()
        states.add(self.q0)
        for c in word:
            local_states = set()
            for q in states:
                local_states.update(self.lambda_closure(q))
            states = local_states.copy()
            local_states.clear()
            for q in states:
                local_states.update(self.d[(q, c)] if (q, c) in self.d.keys() else {})
            states = local_states.copy()
            local_states.clear()

        local_states = set()
        for q in states:
            local_states.update(self.lambda_closure(q))

        return bool(local_states & self.F)


# Converts a regex from infix to postfix
# Using shutting-yard algorithm
class RegexConverter:

    def precedenceOf(self, char):
        precedence = {
            '(': 1,
            '|': 2, # alternate
            '.': 3, # concatenate
            '?': 4, # zero or one
            '*': 4, # zero or more
            '+': 4  # one or more
        }
        return precedence.get(char) if precedence.get(char) is not None else 5

    def addConcatenationPoints(self, word):
        symbols = []
        for i in range(0, len(word) - 1):
            symbols.append(word[i])
            # if self.precedenceOf(word[i]) == 5 and self.precedenceOf(word[i + 1]) == 5:
            #     symbols.append('.')
            if word[i] not in "(|." and word[i + 1] not in "|.+*?)":
                symbols.append('.')
        symbols.append(word[len(word) - 1])
        return "".join(symbols)

    def convert(self, word):
        output = []
        opstack = deque()

        concWord = self.addConcatenationPoints(word)

        # print(concWord)

        for c in concWord:
            if c == '(':
                opstack.appendleft(c)
            elif c == ')':
                peek = opstack.popleft()
                while peek != '(':
                    output.append(peek)
                    peek = opstack.popleft()
            else:
                while len(opstack):
                    peek = opstack.popleft()

                    precedenceOfPeek = self.precedenceOf(peek)
                    precedenceOfCrt = self.precedenceOf(c)

                    if(precedenceOfPeek >= precedenceOfCrt):
                        output.append(peek)
                    else:
                        opstack.appendleft(peek)
                        break

                opstack.appendleft(c)

        while len(opstack):
            output.append(opstack.popleft())

        return "".join(output)

# Creates an NFA from a regular expression
# Using Thompson's construction
class RegexEvaluator:
    statesCounter = 1;

    def createAtomicAutomaton(self, command):
        atomic = Automaton()
        atomic.Q.update([self.statesCounter, self.statesCounter + 1])
        atomic.E.update([command, '_'])
        atomic.F.update([self.statesCounter + 1])
        atomic.q0 = self.statesCounter
        atomic.addTranzition(self.statesCounter, command, self.statesCounter + 1)
        self.statesCounter += 2
        return atomic

    def createAlterateAutomaton(self, automaton1, automaton2):
        alternate = Automaton()
        alternate.Q.update([self.statesCounter])
        alternate.q0 = self.statesCounter
        alternate.Q = automaton1.Q | automaton2.Q | alternate.Q
        alternate.E = automaton1.E | automaton2.E
        alternate.F = automaton1.F | automaton2.F
        alternate.d.update(automaton1.d)
        alternate.d.update(automaton2.d)
        alternate.addTranzition(alternate.q0, '_', automaton1.q0)
        alternate.addTranzition(alternate.q0, '_', automaton2.q0)
        self.statesCounter += 1
        return alternate

    def createConcatenationAutomaton(self, automaton1, automaton2):
        concatenation = Automaton()
        concatenation.Q.update([self.statesCounter])
        concatenation.q0 = self.statesCounter
        concatenation.Q = automaton1.Q | automaton2.Q | concatenation.Q
        concatenation.E = automaton1.E | automaton2.E
        concatenation.F = automaton2.F
        concatenation.d.update(automaton1.d)
        concatenation.d.update(automaton2.d)
        concatenation.addTranzition(concatenation.q0, '_', automaton1.q0)
        for f in automaton1.F:
            concatenation.addTranzition(f, '_', automaton2.q0)
        self.statesCounter += 1
        return concatenation

    def createZeroOneAutomaton(self, automaton1):
        zeroOne = Automaton()
        zeroOne.Q.update([self.statesCounter, self.statesCounter + 1])
        zeroOne.q0 = self.statesCounter
        zeroOne.Q = zeroOne.Q | automaton1.Q
        zeroOne.E = automaton1.E
        zeroOne.F = automaton1.F
        zeroOne.F.update([self.statesCounter + 1])
        zeroOne.d = automaton1.d
        zeroOne.addTranzition(self.statesCounter, '_', self.statesCounter + 1)
        zeroOne.addTranzition(self.statesCounter, '_', automaton1.q0)
        self.statesCounter += 2
        return zeroOne

    def createZeroMoreAutomaton(self, automaton1):
        zeroMore = Automaton()
        zeroMore.Q.update([self.statesCounter, self.statesCounter + 1])
        zeroMore.q0 = self.statesCounter
        zeroMore.Q = zeroMore.Q | automaton1.Q
        zeroMore.E = automaton1.E
        zeroMore.F.update([self.statesCounter + 1])
        zeroMore.d = automaton1.d
        zeroMore.addTranzition(self.statesCounter, '_', self.statesCounter + 1)
        zeroMore.addTranzition(self.statesCounter, '_', automaton1.q0)
        for f in automaton1.F:
            zeroMore.addTranzition(f, '_', self.statesCounter)
        self.statesCounter += 2
        return zeroMore

    def createOneMoreAutomaton(self, automaton1):
        oneMore = Automaton()
        oneMore.Q.update([self.statesCounter, self.statesCounter + 1])
        oneMore.Q = oneMore.Q | automaton1.Q
        oneMore.q0 = automaton1.q0
        oneMore.E = automaton1.E
        oneMore.F.update([self.statesCounter + 1])
        oneMore.d = automaton1.d
        for f in automaton1.F:
            oneMore.addTranzition(f, '_', self.statesCounter)
        oneMore.addTranzition(self.statesCounter, '_', automaton1.q0)
        oneMore.addTranzition(self.statesCounter, '_', self.statesCounter + 1)
        self.statesCounter += 2
        return oneMore;

    def compileRegex(self, regex):
        converter = RegexConverter()
        postfixRegex = converter.convert(regex)
        partials = deque()
        for c in postfixRegex:
            if c == '.':
                e2 = partials.pop()
                e1 = partials.pop()
                concat = self.createConcatenationAutomaton(e1, e2)
                partials.append(concat)
            elif c == '|':
                e2 = partials.pop()
                e1 = partials.pop()
                alternate = self.createAlterateAutomaton(e1, e2)
                partials.append(alternate)
            elif c == '?':
                e = partials.pop()
                zeroOne = self.createZeroOneAutomaton(e)
                partials.append(zeroOne)
            elif c == '*':
                e = partials.pop()
                zeroMore = self.createZeroMoreAutomaton(e)
                partials.append(zeroMore)
            elif c == '+':
                e = partials.pop()
                oneMore = self.createOneMoreAutomaton(e)
                partials.append(oneMore)
            else:
                atom = self.createAtomicAutomaton(c)
                partials.append(atom)

        return partials.pop()

def main():

    evaluator = RegexEvaluator()
    automaton = evaluator.compileRegex("ab|cd");

    automaton.show()

    print(automaton.evaluate("acd"))


if __name__ == "__main__":
    main()
