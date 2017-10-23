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

def binary_search(numero, arreglo, low, upp):
    mid = (upp + low) // 2

    print(upp, low)
    
    if low > upp:
        if numero > arreglo[low]:
            return low
        elif numero < arreglo[upp]:
            return upp
    elif numero == arreglo[mid]:
        return mid
    elif numero < arreglo[mid]:
        return binary_search(numero, arreglo, low, mid - 1)
    else:
        return binary_search(numero, arreglo, mid + 1, upp)

T = input()

for cases in range(int(T)):
    L, U = input().strip().split()

    lower = binary_search(int(L), primos, 0, len(primos) - 1)
    upper = binary_search(int(U), primos, 0, len(primos) - 1)
    
    while primos[lower + 1] < int(L):
        lower += 1

    while primos[upper - 1] > int(U):
        upper -= 1

    diffs = [t - s for s,t in zip(primos[lower:upper],primos[lower+1:upper])]

    count = Counter(diffs)

    max1 = count.most_common()[0][1]
    max2 = 0
    if(len(count.most_common()) > 1): max2 = count.most_common()[1][1]
    
    if max2 == 0:
        print("The jumping champion is " + str(max1))
    elif max1 > max2:
        print("The jumping champion is " + str(max1))
    else:
        print("No jumping champion")
