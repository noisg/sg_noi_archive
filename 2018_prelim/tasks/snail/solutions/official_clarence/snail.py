raw_input = input # python 2?
from builtins import input

INF = 1012345678012345678
BIG = 1000000000000
H, N = map(int, input().split())
assert(1<=H and H<=BIG)
assert(1<=N and N<=10000)
printed = False
P = []
simulate = []
# input data into P
P = list(map(int, input().split()))
# simulate for 2 days
simulate.append(0) # height at start of each phase
for i in range(2*N): # people may forget this
    simulate.append(max(simulate[i]+P[i%N], 0)) # people may leave out max
    if simulate[i+1] >= H: # >= is intended
        print("%d %d\n" % (i/N, i%N))
        printed = True
        break

increment = 0
if not printed:
    for i in range(N):
        increment += P[i]
    if increment <= 0:
        # not possible anymore
        print("-1 -1\n")
        printed = True

if not printed:
    bestDays = INF
    phase = 0
    for i in range(N):
        days = 1+(H-simulate[N+i+1]+increment-1)//increment;
        if bestDays > days:
            bestDays = days
            phase = i
    print("%d %d\n" % (bestDays, phase))
    printed = True
