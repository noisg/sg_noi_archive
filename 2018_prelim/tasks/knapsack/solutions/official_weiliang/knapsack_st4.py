S, N = map(int, raw_input().split())
dp = [0]*(S+1)

for _ in range(N):
	V, W, K = map(int, raw_input().split())
	x = 0
	while K > 0:
		if (2**x >= K):
			w = W*K
			v = V*K
			K = 0
		else:
			w = (2**x) * W
			v = (2**x) * V
			K -= 2**x
			x = x + 1
		for s in range(S, w-1, -1):
			dp[s] = max(dp[s], dp[s-w] + v)

print (max(dp))