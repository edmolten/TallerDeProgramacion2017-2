from math import factorial
import sys

for x in sys.stdin:
    if x == "\n":
        break
    n = int(x)
    a= factorial(2*n)
    b = factorial(n+1)
    c = factorial(n)
    print(a//(b*c))
