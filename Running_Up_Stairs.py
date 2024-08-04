def factorial(n: int) -> int:
    ret = 1
    for i in range(1, n+1):
        ret *= i
    return ret


def permutaion_with_duplicates2(n: int, dn1: int, dn2: int) -> int:
    return int(factorial(n)/int(factorial(dn1)*factorial(dn2)))


def getInts() -> tuple[int, ...]:
    return tuple(map(int, input().split()))


def main():
    t,  = getInts()
    for _ in range(t):
        n, = getInts()
        k = 0
        maxDoubles = n // 2
        for i in range(maxDoubles+1):
            nDouble = i
            nSingle = n - (2 * nDouble)
            k += permutaion_with_duplicates2(nDouble +
                                             nSingle, nDouble, nSingle)
        print(int(k))


main()
