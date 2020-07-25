import java.io.*;
import java.util.*;

public class Aesthetic {

    static class Reader
    {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do
            {
                ret = ret * 10 + c - '0';
            }  while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }
        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }
    }
    static class Pf4 implements Comparable<Pf4>{
        long one;
        int two,three,four;
        Pf4(long a, int b, int c, int d){
            this.one = a;
            this.two = b;
            this.three = c;
            this.four = d;
        }
        public int compareTo(Pf4 x){
            if(this.one!=x.one){
                if(this.one>x.one)return 1;
                else return -1;
            }
            if(this.two!=x.two)return this.two - x.two;
            if(this.three!=x.three)return this.three - x.three;
            return this.four - x.four;

        }
    }
    static class Pf3 implements Comparable<Pf3>{
        int two,three,one;
        Pf3(int a, int b, int c){
            this.one = a;
            this.two = b;
            this.three = c;
        }
        public int compareTo(Pf3 x){
            if(this.one!=x.one)return this.one - x.one;
            if(this.two!=x.two)return this.two - x.two;
            return this.three - x.three;

        }
    }
    static int[][] A = new int[300000][4];
    static long[][] r = new long[2][300000];
    static boolean[] vt = new boolean[300000], f = new boolean[300000];
    static int[] p = new int[300000], q = new int[300000], d = new int[300000], id = new int[300000];
    static ArrayList<Pf3>[] adj = new ArrayList[300000];
    static PriorityQueue<Pf4> pq = new PriorityQueue<Pf4>(11);//, new Pf4(0,0,0,0));

    static int frt(int i) {if (i == id[i]) {return i;} else {return id[i] = frt(id[i]);}}

    static void it(int i, int t, int o, int l, long v) {
     //   System.err.println("! " + i + " " + t + " " + o + " " + l + " " + v);
        if (vt[i]) return;
        vt[i] = true;
        if (t == 0) {p[i] = o; q[i] = l; d[i] = d[o] + (i > 0 ? 1 : 0);}
        r[t][i] = v;
        for (int j = 0; j < adj[i].size(); ++j) if (!vt[adj[i].get(j).one]) pq.offer(new Pf4(v + adj[i].get(j).two, adj[i].get(j).one,i, adj[i].get(j).three));
    }

    public static void main(String args[]) throws IOException {
        Reader reader = new Reader();
        int N = reader.nextInt(), M = reader.nextInt(), a, b, x, i, j;
        long l, h = 300000000000000L, c;
        boolean e;
        for (i = 0; i < N; ++i) adj[i] = new ArrayList<Pf3>();
        for (i = 0; i < M; ++i) {for (j = 0; j < 3; ++j) A[i][j] = reader.nextInt(); adj[--A[i][0]].add(new Pf3(--A[i][1], A[i][2], i)); adj[A[i][1]].add(new Pf3(A[i][0], A[i][2], i));}
        for (i = M - 2; i > -1; --i) A[i][3] = Math.max(A[i + 1][2], A[i + 1][3]);
        it(0, 0, 0, -1, 0);
        while (pq.size() > 0) {x = pq.peek().two; c = pq.peek().one; a = pq.peek().three; b = pq.peek().four; pq.poll(); it(x, 0, a, b, c);}
        for (i = 0; i < N; ++i) vt[i] = false;
        it(N - 1, 1, N - 1, -1, 0);
        while (pq.size() > 0) {x = pq.peek().two; c = pq.peek().one; a = pq.peek().three; b = pq.peek().four; pq.poll(); it(x, 1, a, b, c);}
        l = r[0][N - 1];
        while (l < h) {
            e = false;
            c = (l + h + 1) / 2;
            System.err.println("? " + l + " " + h + ": " + c);
            for (i = 0; i < N; ++i) {id[i] = p[i]; if (i > 0) f[q[i]] = true;}
            for (i = N - 1; i > 0; i = p[i]) id[i] = i;
            for (i = 0; i < M; ++i) if (!f[i] && (r[0][A[i][0]] + A[i][2] + r[1][A[i][1]] < c || r[0][A[i][1]] + A[i][2] + r[1][A[i][0]] < c)) {
                a = frt(A[i][0]);
                b = frt(A[i][1]);
                if (d[a] > d[b]) {a ^= b; b ^= a; a ^= b;}
                while (a != b) {id[b] = p[b]; b = frt(b);}
            }
            for (i = frt(N - 1); i > 0 && !e; i = frt(p[i])) e = (c <= r[0][A[q[i]][0]] + A[q[i]][2] + A[q[i]][3] + r[1][A[q[i]][1]] && c <= r[0][A[q[i]][1]] + A[q[i]][2] + A[q[i]][3] + r[1][A[q[i]][0]]);
            if (e) l = c;
            else h = c - 1;
        }
        System.out.print((l + h) / 2);
    }
}
