from math import factorial
import sys

while True:
    x = input()
    if not x:
        break
    n = int(x)
    a= factorial(2*n)
    b = factorial(n+1)
    c = factorial(n)
    print(str(a//(b*c)))
    print("")
    #if x != "":
    #    print()
