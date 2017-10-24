import sys
import math

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

primes = hera(1000000)

while True:
    N = int(input())
    if not N:
        break
    powers = dict([(p, int(math.log(N, p))) for p in primes if p <= max(5, N)])
    # print N, powers
    result = 1
    for p in primes:
        if p > N:
            break
        if p != 2 and p != 5:
            result *= pow(p, powers[p], 10)

    if powers[5] > powers[2]:
        for i in range(powers[5] - powers[2]):
            result = result * 5 % 10
    elif powers[2] > powers[5]:
        for i in range(powers[2] - powers[5]):
            result = result * 2 % 10
    print result