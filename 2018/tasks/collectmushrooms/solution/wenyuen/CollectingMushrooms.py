import sys

header_line = sys.stdin.readline()
header_line = header_line.split(" ")
R = int(header_line[0])
C = int(header_line[1])
D = int(header_line[2])
K = int(header_line[3])
G = []
for i in range(R):
	G.append(sys.stdin.readline())

P = []
for i in range(R + 1):
	P_row = []
	for j in range(C + 1):
		P_row.append(0)
	P.append(P_row)

for i in range(R):
	for j in range(C):
		if G[i][j] == 'S':
			li = max(0, i - D)
			hi = min(R - 1, i + D)
			lj = max(0, j - D)
			hj = min(C - 1, j + D)
			P[li][lj] += 1
			P[li][hj + 1] -= 1
			P[hi + 1][lj] -= 1
			P[hi + 1][hj + 1] += 1

for i in range(1, R):
	for j in range(C):
		P[i][j] += P[i - 1][j]
for i in range(R):
	for j in range(1, C):
		P[i][j] += P[i][j - 1]


ans = 0
for i in range(R):
	for j in range(C):
		if G[i][j] == 'M' and P[i][j] >= K:
			ans += 1
			
print(ans)
