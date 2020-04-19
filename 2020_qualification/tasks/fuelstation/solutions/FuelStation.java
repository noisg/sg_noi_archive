import java.io.DataInputStream;
import java.io.IOException;
import java.util.*;
import java.lang.Math.*;

public class FuelStation {
    static class station implements Comparable<station> {
        public int X, A, B;
        public station() {}
        public station(int _X, int _A, int _B) {
            X = _X;
            A = _A;
            B = _B;
        }
        public int compareTo(station o) {
            if (X != o.X) return X - o.X;
            if (A != o.A) return A - o.A;
            return B - o.B;
        }
    }

    static class Pair implements Comparable<Pair> {
        public int first, second;
        public Pair() {}
        public Pair(int _first, int _second) {
            first = _first;
            second = _second;
        }
        public int compareTo(Pair o) {
            if (first != o.first) return first - o.first;
            return second - o.second;
        }
    }

    static class SegmentTree {
        private long[] V;
        private long[] LAZY;
        SegmentTree() {
            V = new long[1500010];
            LAZY = new long[1500010];
        }
        public long val(int x) { return V[x] + LAZY[x]; }
        private void push(int x) {
            if (LAZY[x] != 0) {
                LAZY[x << 1] += LAZY[x];
                LAZY[x << 1 | 1] += LAZY[x];
                V[x] += LAZY[x];
                LAZY[x] = 0;
            }
        }

        public void update(int node, int S, int E, int QS, int QE, int QV) {
            if (QS <= S && E <= QE) {
                LAZY[node] += QV;
                return;
            }
            push(node);
            int M = S + (E - S) / 2;
            if (QE <= M) update(node << 1, S, M, QS, QE, QV);
            else if (QS > M) update(node << 1 | 1, M + 1, E, QS, QE, QV);
            else {
                update(node << 1, S, M, QS, M, QV);
                update(node << 1 | 1, M + 1, E, M + 1, QE, QV);
            }
            V[node] = Math.min(val(node << 1), val(node << 1 | 1));
        }
    }

    static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
        public Reader() {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        public int nextInt() throws IOException {
            int ret = 0;
            byte c = read();
            while (c <= ' ') {
                c = read();
            }
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            return ret;
        }

        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1) {
                buffer[0] = -1;
            }
        }

        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead) {
                fillBuffer();
            }
            return buffer[bufferPointer++];
        }
    }

    public static void main(String[] args) throws IOException {
        Reader reader = new Reader();
        int N = reader.nextInt();
        int D = reader.nextInt();
        SegmentTree root = new SegmentTree();
        station[] STN = new station[300010];
        int[] NXT = new int[300010];
        ArrayList<Pair> V = new ArrayList<Pair>();
        for (int a = 1; a <= N; ++a) {
            int X = reader.nextInt();
            int A = reader.nextInt();
            int B = reader.nextInt();
            STN[a] = new station(X, A, B);
        }
        Arrays.sort(STN, 1, N + 1);
        int XPTR = 1;
        STN[N + 1] = new station(D, 0, D);
        for (int a = 1; a <= N + 1; ++a) if (STN[a].X != STN[XPTR].X)
            for (; XPTR < a; ++XPTR) NXT[XPTR] = a;
        NXT[N + 1] = N + 1;
        for (int a = 1; a <= N + 1; ++a) V.add(new Pair(STN[a].B, a));
        Collections.sort(V);
        for (int a = 0; a <= N; ++a) root.update(1, 1, N + 1, V.get(a).second, V.get(a).second, -STN[V.get(a).second].X);
        for (int a = 0; a <= N; ++a)
            root.update(1, 1, N + 1, NXT[V.get(a).second], N + 1, STN[V.get(a).second].A);
        int F = 0, BPTR = 0;
        for (int a = 0; a <= N; ++a) {
            root.update(1, 1, N + 1, 1, N + 1, V.get(a).first - F);
            if (a > 0 && V.get(a).first != F)
                for (; BPTR < a; ++BPTR)
                    root.update(1, 1, N + 1, NXT[V.get(BPTR).second], N + 1, -STN[V.get(BPTR).second].A);
            F = V.get(a).first;
            long mval = root.val(1);
            if (mval >= 0) {
                System.out.println(F - mval);
                return;
            }
        }
    }
}
