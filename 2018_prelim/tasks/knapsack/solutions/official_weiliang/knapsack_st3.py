S, N = map(int, raw_input().split())
dp = [0]*(S+1)

for _ in range(N):
	V, W, K = map(int, raw_input().split())
	for k in range(K):
		for s in range(S, W-1, -1):
			dp[s] = max(dp[s], dp[s-W] + V)

print (max(dp))