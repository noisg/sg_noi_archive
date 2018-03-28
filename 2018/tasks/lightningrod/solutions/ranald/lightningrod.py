import sys
lines = sys.stdin.readlines()
N = int(lines[0])
st = {}
l = 0
for i in range(N):
    x, y = map(int, lines[i+1].split(" "))
    add = True
    while (l > 0):
        tx, ty = st[l]
        if (x - tx) <= (ty - y):
            add = False
            break
        if (x - tx) <= (y - ty):
            l = l-1
        else:
            break
    if add:
        l = l + 1
        st[l] = (x, y)
print (l)