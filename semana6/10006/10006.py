def hera(n):
    composites = n*[False]
    for i in range(2, n):
        if not composites[i]:
            j = 2
            while j * i < n:
                composites[i * j] = True
                j += 1
    return composites


def clever_mod(a, e, r):
    aux = a
    res = 1
    while e:
        if e & 1:
            res *= aux
            res %= r
        aux = aux * aux
        aux %= r
        e //= 2
    return res


def check_lower_mods(n):
    for i in range(2, n):
        if clever_mod(i, n, n) != i:
            return False
    return True

composites = hera(65001)

while True:
    n = input()
    if n == "0":
        break
    n = int(n)
    if  composites[n] and check_lower_mods(n):
        print("The number " + str(n) + " is a Carmichael number.")
    else:
        print(str(n) + " is normal.")
