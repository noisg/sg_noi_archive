N, M = map(int, raw_input().split())
cnt = [0]*(N+M+1)
for i in range(N+M-1):
	u, v = map(int, raw_input().split())
	cnt[u] = cnt[u] + 1
	cnt[v] = cnt[v] + 1
	
fac = [0]*(N+M+1)
for i in range(1, N+M+1):
	for k in range(2, cnt[i]):
		print ("%d %d" % (k, 1))
