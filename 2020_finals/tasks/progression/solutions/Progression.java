import java.io.*;
import java.util.*;
import java.lang.Math.*;

public class Progression {
    static long[] D;
    static long[] B;

    static class qval {
        public int len, prefix_len, suffix_len, subarray_len;
        public long sum, prefix_val, suffix_val, subarray_val;
        public qval() {}
        public void init(long val) {
            len = 1; sum = val;
            subarray_len = 0;
            subarray_val = 0;
            prefix_len = suffix_len = 1;
            prefix_val = suffix_val = val;
        }
        public void add(long val) {
            prefix_val += val;
            suffix_val += val;
            subarray_val += val;
            sum += val * len;
        }
        public void set(long val) {
            prefix_val = suffix_val = subarray_val = val;
            prefix_len = suffix_len = len;
            subarray_len = Math.max(0, len - 2);
            sum = val * len;
        }
    }

    static class SegmentTree {
        private qval[] V;
        private boolean[] lset;
        private long[] lazy_set;
        private long[] lazy_add;
        SegmentTree() {
            lazy_set = new long[1500010];
            lazy_add = new long[1500010];
            lset = new boolean[1500010];
            V = new qval[1500010];
        }
        public void build(int node, int S, int E) {
            V[node] = new qval();
            if (S == E) {
                V[node].init(B[S]);
                return;
            }
            int M = S + (E - S) / 2;
            build(node << 1, S, M);
            build(node << 1 | 1, M + 1, E);
            combine(V[node], V[node << 1], V[node << 1 | 1]);
        }
        private void combine(qval ret, qval left, qval right) {
            ret.len = left.len + right.len;
            ret.sum = left.sum + right.sum;

            ret.prefix_len = left.prefix_len;
            ret.prefix_val = left.prefix_val;
            if (left.prefix_len == left.len && left.prefix_val == right.prefix_val) {
                ret.prefix_len = left.len + right.prefix_len;
                ret.prefix_val = left.prefix_val;
            }

            ret.suffix_len = right.suffix_len;
            ret.suffix_val = right.suffix_val;
            if (right.suffix_len == right.len && left.suffix_val == right.suffix_val) {
                ret.suffix_len = right.len + left.suffix_len;
                ret.suffix_val = right.suffix_val;
            }

            if (left.subarray_len > right.subarray_len) {
                ret.subarray_len = left.subarray_len;
                ret.subarray_val = left.subarray_val;
            } else {
                ret.subarray_len = right.subarray_len;
                ret.subarray_val = right.subarray_val;
            }
            if (Math.min(left.len - 1, left.suffix_len) > ret.subarray_len) {
                ret.subarray_len = Math.min(left.len - 1, left.suffix_len);
                ret.subarray_val = left.suffix_val;
            }
            if (Math.min(right.len - 1, right.prefix_len) > ret.subarray_len) {
                ret.subarray_len = Math.min(right.len - 1, right.prefix_len);
                ret.subarray_val = right.prefix_val;
            }
            if (left.suffix_val == right.prefix_val &&
                Math.min(left.len - 1, left.suffix_len) +
                Math.min(right.len - 1, right.prefix_len) > ret.subarray_len) {
                ret.subarray_len = Math.min(left.len - 1, left.suffix_len) +
                    Math.min(right.len - 1, right.prefix_len);
                ret.subarray_val = left.suffix_val;
            }
        }
        private void push(int node) {
            if (lset[node]) {
                rset(node << 1, lazy_set[node]);
                rset(node << 1 | 1, lazy_set[node]);
                lset[node] = false;
                lazy_set[node] = 0;
            }
            if (lazy_add[node] != 0) {
                radd(node << 1, lazy_add[node]);
                radd(node << 1 | 1, lazy_add[node]);
                lazy_add[node] = 0;
            }
        }
        public void radd(int node, long QV) {
            if (lset[node]) V[node].set(lazy_set[node] += QV);
            else {
                lazy_add[node] += QV;
                V[node].add(QV);
            }
        }
        public void rset(int node, long QV) {
            lset[node] = true;
            lazy_add[node] = 0;
            V[node].set(lazy_set[node] = QV);
        }
        public qval query(int node, int S, int E, int QS, int QE) {
            if (QS <= S && E <= QE) return V[node];
            push(node);
            int M = S + (E - S) / 2;
            if (QE <= M) return query(node << 1, S, M, QS, QE);
            if (QS > M) return query(node << 1 | 1, M + 1, E, QS, QE);
            qval ret = new qval();
            combine(ret, query(node << 1, S, M, QS, M), query(node << 1 | 1, M + 1, E, M + 1, QE));
            return ret;
        }
        public void add(int node, int S, int E, int QS, int QE, long QV) {
            if (QS <= S && E <= QE) {
                radd(node, QV);
                return;
            }
            push(node);
            int M = S + (E - S) / 2;
            if (QE <= M) add(node << 1, S, M, QS, QE, QV);
            else if (QS > M) add(node << 1 | 1, M + 1, E, QS, QE, QV);
            else {
                add(node << 1, S, M, QS, M, QV);
                add(node << 1 | 1, M + 1, E, M + 1, QE, QV);
            }
            combine(V[node], V[node << 1], V[node << 1 | 1]);
        }
        public void set(int node, int S, int E, int QS, int QE, long QV) {
            if (QS <= S && E <= QE) {
                rset(node, QV);
                return;
            }
            push(node);
            int M = S + (E - S) / 2;
            if (QE <= M) set(node << 1, S, M, QS, QE, QV);
            else if (QS > M) set(node << 1 | 1, M + 1, E, QS, QE, QV);
            else {
                set(node << 1, S, M, QS, M, QV);
                set(node << 1 | 1, M + 1, E, M + 1, QE, QV);
            }
            combine(V[node], V[node << 1], V[node << 1 | 1]);
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
            Boolean flip = false;
            byte c = read();
            while (c < '0' || c > '9') {
                if (c == '-') flip = true;
                c = read();
            }
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            return flip ? -ret : ret;
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
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        int N = reader.nextInt();
        int Q = reader.nextInt();
        D = new long[300010];
        B = new long[300010];
        for (int a = 1; a <= N; ++a) {
            D[a] = reader.nextInt();
            B[a] = D[a] - D[a - 1];
        }
        SegmentTree root = new SegmentTree();
        root.build(1, 1, N);
        while (Q-- > 0) {
            int op = reader.nextInt();
            if (op == 1) {
                int L, R; long S, C;
                L = reader.nextInt(); R = reader.nextInt();
                S = reader.nextInt(); C = reader.nextInt();
                root.add(1, 1, N, L, L, S);
                if (L != R) root.add(1, 1, N, L + 1, R, C);
                if (R != N) root.add(1, 1, N, R + 1, R + 1, -(S + (R - L) * C));
            } else if (op == 2) {
                int L, R; long S, C;
                L = reader.nextInt(); R = reader.nextInt();
                S = reader.nextInt(); C = reader.nextInt();
                long old_sum = root.query(1, 1, N, L, R).sum;
                long prefix = (L == 1 ? 0 : root.query(1, 1, N, 1, L - 1).sum);
                root.set(1, 1, N, L, L, S - prefix);
                if (L != R) root.set(1, 1, N, L + 1, R, C);
                if (R != N) {
                    long new_sum = (S - prefix) + (R - L) * C;
                    root.add(1, 1, N, R + 1, R + 1, old_sum - new_sum);
                }
            } else {
                int L, R;
                L = reader.nextInt(); R = reader.nextInt();
                qval ret = root.query(1, 1, N, L, R);
                int len = Math.max(ret.prefix_len, ret.subarray_len + 1);
                len = Math.max(len, ret.suffix_len + 1);
                len = Math.min(len, ret.len);
                out.write(Integer.toString(len));
                out.write("\n");
            }
        }
        out.flush();
    }
}
