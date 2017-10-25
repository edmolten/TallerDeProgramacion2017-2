def heras(n):  # retorna una lista X donde X[i] es el mayor primo que divide a i
    prime_divisors = [1 for _ in range(n)]
    for i in range(2, n):
        if prime_divisors[i] == 1:
            for j in range(i, n, i):
                prime_divisors[j] = i
    return prime_divisors

n = int(input())
table = [int(x) for x in input().split()]
max_prime_divisors = heras(n + 1)
m = n
while m > 1:
    max_prime_divisor = max_prime_divisors[m]
    if max_prime_divisor == 2:
        if n % 4 == 0:
            max_prime_divisor = 4
        else:
            break
    jump = n // max_prime_divisor  # el salto es la menor division por primo
    start_positions = range(jump)
    for i in start_positions:  # probar comenzar a contar desde la posición 0 hasta la jump - 1
        can_make_poligon = True
        test_positions = range(i, n, jump)
        for j in test_positions:  # probar cada posición de la mesa, saltando jump
            if not table[j]:  # si no esta de buen humor, no funciona este caso
                can_make_poligon = False
                break
        if can_make_poligon:
            print('YES')
            exit(0)
    m //= max_prime_divisor  # probar con cada sub-conjunto de puntos
print('NO')