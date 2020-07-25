import sys

N = int(input())
P = [0] * N

D = [int(x) for x in input().split(" ")]
D.append(0)

for x in range(N - 1):
    if x:
        D[x] += D[x - 1]

if max(D) - min(D) != N - 1:
    print("-1")
    sys.exit()

P[0] = N - max(D)
for x in range(1, N):
    P[x] = P[0] + D[x - 1]

print(" ".join(str(_) for _ in P))
