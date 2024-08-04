t = int(input())


def p__t(c, comp):
    fs = list(comp.keys())
    fs.sort()
    fs.reverse()
    power = 0

    for f in fs:
        ws = comp[f]
        ws.sort()
        for w in ws:
            if (w <= c):
                power += f
                c -= w
    return power


for ti in range(t):
    c, n = map(int, input().split())
    comp = {}
    for ni in range(n):
        w, f = map(int, input().split())
        if not comp.get(f):
            comp[f] = list()
        comp[f].append(w)
    res = p__t(c, comp)
    print(res)
