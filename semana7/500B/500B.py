N= 300
n = 0
inp = [0]* (N+1)
outp = [-1] * (N+1)
visited = [False] * (N+1)
A = [[] for i in range(N+1)]
pos = []
num = []



def dfs(index):
    if visited[index]:
        return
    visited[index] = True
    pos.append(index)
    num.append(inp[index])
    for i in range(1,n+1):
        if A[index][i-1] == "1" and not(visited[i]):
            dfs(i)


n = int(input())
a = input()
a = a.split()
for i in range(len(a)):
    inp[i]=int(a[i])

for j in range(n):
    A[j] = input()

for i in range(1,n+1):
    if visited[i]:
        continue
    dfs(i)
    pos.sort()
    num.sort()
    for j in range(len(pos)):
        outp[pos[j]] = num[j]
    pos = []
    num = []

for i in range(1,n+1):
    if outp[i] < 0:
        outp[i]=inp[i]

for i in range(1,n+1):
    if i != n-1:
        print(outp[i], end=" ")
    else:
        print(outp[i], end="")