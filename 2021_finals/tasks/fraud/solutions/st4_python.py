import sys
import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

N = int(input())
A = [int(x) for x in input().split()]
B = [int(x) for x in input().split()]

m_left, m_right = 1e9, 0
can = True

for x in range(N - 1):
    if (A[x] <= A[x + 1]) and (B[x] <= B[x + 1]):
        can = False
        break
    elif ((A[x] >= A[x + 1]) and (B[x] > B[x + 1])) or \
         ((A[x] > A[x + 1]) and (B[x] >= B[x + 1])):
         continue
    else:
        right = (B[x] - B[x + 1]) > 0
        m = (A[x + 1] - A[x]) / (B[x] - B[x + 1])
        if right:
            m_right = max(m_right, m)
        else:
            m_left = min(m_left, m)

can &= m_left > m_right
print(["NO", "YES"][can])