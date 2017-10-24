'''
void
sieve()
{
    bool
isComposite[MAX] = {false};
for (int
i = 2;
i * i <= MAX;
i + +)
{
if (isComposite[i] == false)
for (int j=2; j * i <= MAX; j++)
isComposite[i * j] = true;
}

// Store all prime numbers in vector primes[]
for (int i=2; i <= MAX; i++)
if (isComposite[i] == false)
primes.push_back(i);
}
'''


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

n = 1000
p = hera(n)
print(p)