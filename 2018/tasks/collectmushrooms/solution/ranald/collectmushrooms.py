import os
grid = os.read(0, 500000).decode("ascii").split("\n")
N, M, D, K = map(int, grid[0].split(" "))
rsq = [[0] * (M+1)]
for i in range(N):
	row = [0]
	s = 0
	for j in range(M):
		s += rsq[i][j+1] - rsq[i][j] + (grid[i+1][j] == 'S')
		row.append(s)
	rsq.append(row)
	
def sumArea(x, y):
	a = max(0, x-1-D)
	b = max(0, y-1-D)
	c = min(x+D, N)
	d = min(y+D, M)
	return rsq[c][d] - rsq[a][d] - rsq[c][b] + rsq[a][b]

ans = sum([(grid[i][j] == 'M' and sumArea(i, j+1) >= K) for j in range(M) for i in range(1, N+1)])
print (ans)
