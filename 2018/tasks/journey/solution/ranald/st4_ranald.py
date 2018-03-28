import sys
N, M, H = map(int, sys.stdin.readline().split())
adjList = [[] for i in range(N)]
dp = [[0]*M for i in range(N)]
for a in range(N-1):
	line = list(map(int, sys.stdin.readline().split()))
	for k in range(H):
		b = line[k*2]
		c = line[k*2+1]
		if b > a:
			adjList[b].append((a, c))

dp[0][0] = 1
for i in range(1, N):
	s = dp[i-1][0]
	for k in range(1, M):
		s += dp[i-1][k]
		dp[i-1][k] = s
	for k in range(M):
		q = 0
		for x, c in adjList[i]:
			if c <= k:
				q += dp[x][k-c]
				if q > 500000001:
					q = 500000001
					break
		dp[i][k] = q
		if q > 500000001 and i < N-1:
			break


print (" ".join(map(str, dp[N-1])))