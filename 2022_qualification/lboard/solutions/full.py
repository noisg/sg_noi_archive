x = input().split()
n = int(x[0])
m = int(x[1])
a = [[] for j in range(n)]
for i in range(n):
	a[i] = [ int(x) for x in input().split()]
ans = a[0][0]
row_ans = [([0] * (m+1)) for j in range(n)]
for x in range(n):
    current = 0
    for y in range(m):
        row_ans[x][y] = current
        current += a[x][y]
        if (current < 0):
            current = 0
    current = 0
    for y in range(m-1, -1, -1):
        row_ans[x][y] = max(row_ans[x][y], current)
        current += a[x][y]
        if (current < 0):
            current = 0
            
ans = a[0][0]
for y in range(m):
    current = 0
    for x in range(n):
        ans = max(ans, row_ans[x][y] + current + a[x][y])
        current += a[x][y]
        if (current < 0):
            current = 0
    current = 0
    for x in range(n-1, -1, -1):
        ans = max(ans, row_ans[x][y] + current + a[x][y])
        current += a[x][y]
        if (current < 0):
            current = 0
print(ans)
