import sys
n,a,b=map(int, sys.stdin.readline().strip().split()) #assuming n,a,b are in one line
A=list(map(int, sys.stdin.readline().strip().split()))
B=list(map(int, sys.stdin.readline().strip().split()))
ans=sum(A)
for i in range(n):
    B[i]-=A[i]
B=sorted(B,reverse=True)
for i in range(b):
    ans+=B[i]
print(ans)
