from collections import deque


class Automaton:
    def __init__(self):
        self.Q = set()
        self.E = set()
        self.F = set()
        self.q0 = None
        self.d = {}

    def read_file(self, filename):
        f = open(filename, 'r')
        self.Q.update(f.readline().rstrip().split(' '))
        self.E.update(f.readline().rstrip().split(' '))
        self.E.update('_')
        self.F.update(f.readline().rstrip().split(' '))
        self.q0 = f.readline().rstrip()

        for line in f:
            command = line.rstrip().split(' ')
            # self.d.setdefault((command[0], command[1]), {}).update(command[2])
            if (command[0], command[1]) in self.d.keys():
                self.d[(command[0], command[1])].update(command[2])
            else:
                self.d.update({(command[0], command[1]): {command[2]}})

    def read_dummy(self):
        self.Q.update([0, 1, 2, 3, 4, 5, 6])
        self.E.update(['a', 'b', '_'])
        self.F.update([2, 6])
        self.q0 = 0
        self.d.update({(0, 'a'): {0, 1},
                       (0, 'b'): {2},
                       (0, '_'): {2, 3},
                       (1, '_'): {2},
                       (2, '_'): {4},
                       (2, 'a'): {3},
                       (3, 'a'): {6},
                       (3, 'b'): {3, 6},
                       (3, '_'): {5},
                       (4, 'a'): {6},
                       (4, 'b'): {5},
                       (4, '_'): {6},
                       (5, 'a'): {6},
                       (5, '_'): {2, 6},
                       (6, 'b'): {6}})

    def show(self):
        print("Stari: " + self.Q.__str__())
        print("Alfabet: " + self.E.__str__())
        print("Stari finale: " + self.F.__str__())
        print("Stare initiala: " + self.q0.__str__())
        print("Tranzitii: ")
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

    def check_closures(self):
        for s in self.Q:
            print(self.lambda_closure(s))

    def evaluate(self, word):
        states = set()
        states.add(self.q0)
        for c in word:
            # print(c)
            local_states = set()
            for q in states:
                local_states.update(self.lambda_closure(q))
            states = local_states.copy()
            local_states.clear()
            # print(states)
            for q in states:
                local_states.update(self.d[(q, c)] if (q, c) in self.d.keys() else {})
            states = local_states.copy()
            local_states.clear()
            # print(states)
        local_states = set()
        for q in states:
            local_states.update(self.lambda_closure(q))
        # print(local_states)
        return bool(local_states & self.F)


def main():
    a = Automaton()
    a.read_file('automat2.in')
    # print(a.evaluate("aaaaaaabb"))
    # print(a.evaluate("aaaaaabbbbbbbbabbaaaa"))
    # print(a.evaluate(""))
    # print(a.evaluate("aaaaaabbbbbbbbaaaaabbbbbaaaaa"))
    print(a.evaluate("aaaaab"))
    # a.show()

    # d = {}
    # d.setdefault((1, 2), {}).update({6})

    # print(d[(1, 2)])


if __name__ == "__main__":
    main()
