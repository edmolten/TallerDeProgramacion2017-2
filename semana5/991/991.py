from math import factorial
import sys

first = 1

while True:
    x = sys.stdin.readline().strip()
    if first:
        first = 0
    else:
        print()
    if not x:
        break
    n = int(x)
    a = factorial(2*n)
    b = factorial(n+1)
    c = factorial(n)
    print(a//(b*c))
    #print()

# PICO ESTA MIERDA