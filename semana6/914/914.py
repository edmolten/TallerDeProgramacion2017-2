from collections import Counter

def hera(n):
    primes = []
    composites = [False]*n
    for i in range(2, n):
        j = 2
        while j * i < n:
            composites[i * j] = True
            j += 1
    for i in range(2, n):
        if not composites[i]:
            primes.append(i)
    return primes

primos = hera(1000000)

def binary_search(numero, arreglo):
    lo = 0
    up = len(arreglo) - 1

    while lo < up:
        mid = (lo + up) // 2

        if primos[mid] > numero:
            up = mid
        elif primos[mid] < numero:
            lo = mid + 1
        else:
            return mid;

    return lo

T = input()

for cases in range(int(T)):
    L, U = input().strip().split()

    lower = binary_search(int(L), primos)
    upper = binary_search(int(U), primos)

    if upper - lower == 1:
        if primos[upper] > int(U):
            diffs = list()
        else:
            diffs = [primos[upper] - primos[lower]]
    else:
        diffs = [t - s for s,t in zip(primos[lower:upper],primos[lower+1:upper])]
    count = Counter(diffs)

    if(len(count) > 0):
        max1 = count.most_common()[0][1]
        max2 = 0
        if(len(count.most_common(2)) > 1): max2 = count.most_common(2)[1][1]
        jumping_champion = count.most_common()[0][0]

        if max2 == 0:
            print("The jumping champion is " + str(jumping_champion))
        elif max1 == max2:
            print("No jumping champion")
        else:
            print("The jumping champion is " + str(jumping_champion))
    else:
        print("No jumping champion")

print("")

