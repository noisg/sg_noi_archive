N, M = map(int, raw_input().split())
cnt = [0]*(N+M+1)
for i in range(N+M-1):
	u, v = map(int, raw_input().split())
	cnt[u] = cnt[u] + 1
	cnt[v] = cnt[v] + 1
	
fac = [0]*(N+M+1)
for i in range(1, N+M+1):
	fac[cnt[i]-1] += 1

for k in range(N+M, 1, -1):
	if fac[k] > 0:
		fac[k-1] += fac[k]
		print ("%d %d" % (k, fac[k]))
