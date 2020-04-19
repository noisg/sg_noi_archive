import sys
import threading
sys.setrecursionlimit(1000000)
threading.stack_size(1<<27)
class Work:
    def __call__(self):
        (N, K) = [int(x) for x in sys.stdin.readline().split()]
        adjlist = [[] for _ in range(N)]
        for line in sys.stdin.readlines():
            (A, B, W) = [int(x) for x in line.split()]
            A -= 1
            B -= 1
            adjlist[A].append((B, W))
            adjlist[B].append((A, W))
        ans = []
        def dfs(index, prev, dist):
            max_overflow = -1<<62
            max_underflow = 0;
            for (target, length) in adjlist[index]:
                if target != prev:
                    (type, val) = dfs(target, index, length)
                    if type:
                        if max_overflow < val:
                            max_overflow = val
                    else:
                        if max_underflow < val:
                            max_underflow = val
            if max_overflow >= max_underflow:
                ret = (True, max_overflow - dist)
            else:
                ret = (False, max_underflow + dist)
            if (not ret[0]) and (ret[1] > K):
                ans.append(index)
                ret = (True, K - dist)
            if ret[0] and (ret[1] < 0):
                ret = (False, 0)
            return ret
        dfs(0, -1, 1<<60)
        sys.stdout.write(str(len(ans)) + '\n' + ' '.join([str(x + 1) for x in ans]))
t = threading.Thread(target=Work())
t.start()
t.join()

