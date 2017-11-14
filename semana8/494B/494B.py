MOD = 1e9 + 7
L = 10#100005
st = input()
pattern = input()
st_len = len(st)
pattern_len = len(pattern)
k = -1

par = [-2] * L
f = [-2] * L
tot = [-2] * L
sums = [-2] * L
g = [-2] * L

par[0] = -1
for i in range(1, pattern_len):
    while k >= 0 and pattern[k + 1] != pattern[i]:
        k = par[k]
    if pattern[k+1] == pattern[i]:
        k += 1
    par[i] = k
k = -1
for i in range(0, st_len):
    if k+1 < pattern_len:
        if pattern[k+1] == st[i]:
            k += 1
        else:
            while k >= 0 and pattern[k+1] != st[i]:
                k = par[k]
            if pattern[k+1] == st[i]:
                k += 1
    if k == pattern_len-1:
        g[i] = 1
f[0] = 0
sums[0] = 0
tot[0] = 0
ans = 0
for i in range(1, st_len+1): #podría ser desde 2
    if g[i-1] != -2:
        f[i] = tot[i - pattern_len] + i - pattern_len + 1
        f[i] %= MOD
        sums[i] = f[i] + sums[i - 1]
        sums[i] %= MOD
    else:
        f[i] = f[i - 1]
        sums[i] = f[i] + sums[i - 1]
        sums[i] %= MOD
    tot[i] = sums[i] + tot[i - 1]
    tot[i] %= MOD
    ans += f[i]
    ans %= MOD

print(ans)
