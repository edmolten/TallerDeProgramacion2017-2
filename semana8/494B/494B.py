MOD = 1e9 + 7

s = input()
t = input()
N = len(s)
M = len(t)
k = -1
par = [0]* (100005)
f = [0]* (100005)
tot = [0]* (100005)
g = [0]* (100005)
par[0] = -1

for i in range(2,M): #podria partir desde 1
    while k>=0 and t[k + 1] != t[i]:
        k = par[k]
    if t[k+1] == t[i]:
        k+=1
    par[i] = k
k = -1

for i in range(1,N): #podria partir de 0
    if t[k+1] == s[i]:
        k+=1
    else:
        while k>=0 and t[k+1] != s[i]:
            k = par[k]
        if t[k+1] == s[i]:
            k+=1
    if k == M-1:
        g[i]=1

f[0] = 0
sum[0] = 0
tot[0] = 0
ans = 0

for i in range(2,N+1): #podría ser desde 2
    if g[i-1]:
        f[i] = tot[i - M] + i - M + 1
        f[i] %= MOD
        sum[i] = f[i] + sum[i - 1]
        sum[i] %= MOD
    else:
        f[i] = f[i - 1]
        sum[i] = f[i] + sum[i - 1]
        sum[i] %= MOD

    tot[i] = sum[i] + tot[i - 1]
    tot[i] %= MOD
    ans += f[i]
    ans %= MOD

print(ans)