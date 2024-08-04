s = input()[::-1]
q = int(input())


def p__pi(pi):
    pos1 = 0
    for i, c in enumerate(pi):
        pos2 = s.find(c, pos1)
        if pos2 == -1:
            return i
        pos1 = pos2+1
    return len(pi)


for i in range(q):
    pi = input()[::-1]
    print(p__pi(pi))
