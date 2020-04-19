import java.io.DataInputStream;
import java.io.IOException;
import java.util.*;
import java.io.*;

public class RelayMarathon {
    static final class Reader {
        final private int BUFFER_SIZE = 1 << 20;
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
        public long nextLong() throws IOException {
            long ret = 0;
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

    public static class DirectedEdge {
      int u;
      int w;
      public DirectedEdge(int u, int w) {
        this.u = u;
        this.w = w;
      }
    }

    public static class Edge {
      int u;
      int v;
      int w;
      public Edge(int u, int v, int w) {
        this.u = u;
        this.v = v;
        this.w = w;
      }
    }

    public static class Qitem implements Comparable<Qitem> {
      int first;
      int second;
      public Qitem(int first, int second) {
        this.first = first;
        this.second = second;
      }
      public final int compareTo(Qitem b) {
        if(this.first > b.first) {
          return 1;
        } else if(this.first < b.first) {
          return -1;
        } else {
          return 0;
        }
      }
    }

    public static ArrayList<Edge> E;
    static final int INT_MAX = 1000000003;
    static final int[] S = new int[100005];
    static final int[] dx1 = new int[100005];
    static final int[] dy1 = new int[100005];
    static final int[] d = new int[100005];
    static final int[] p = new int[100005];
    static final int[] skip = new int[100005];
    static final int[] vis = new int[100005];
    static int n, m, k;
    public static ArrayList<DirectedEdge>[] adj;

    static final PriorityQueue<Qitem> Q = new PriorityQueue<>();

    public static void djikstra() {
      while(!Q.isEmpty()) {
        int u = Q.poll().second;
        if(vis[u] == 1)  continue;
        vis[u] = 1;
        for(DirectedEdge nbr : adj[u]) {
          int v = nbr.u, w = nbr.w;
          if(skip[v] == 1)  continue;
          if(d[u] + w < d[v]) {
            d[v] = d[u] + w;
            Q.add(new Qitem(d[v], v));
            p[v] = p[u];
          }
        }
      }
    }

    public static void run(int src) {
      while(!Q.isEmpty()) Q.poll();
      for(int i = 1; i <= n; i++) {
        d[i] = INT_MAX;
        vis[i] = 0;
      }
      d[src] = 0;
      p[src] = src;
      Q.add(new Qitem(0, src));
      djikstra();
    }

    public static Edge run_nearest() {
      while(!Q.isEmpty()) Q.poll();
      for(int i = 1; i <= n; i++) {
        d[i] = INT_MAX;
        vis[i] = 0;
      }
      for(int i = 0; i < k; i++) {
        int u = S[i];
        if(skip[u] == 1)  continue;
        Q.add(new Qitem(0, u));
        d[u] = 0;
        p[u] = u;
      }
      djikstra();
      int ans = INT_MAX, a = -1, b = -1;
      for(Edge e : E) {
        int u = e.u, v = e.v, w = e.w;
        if(skip[u] == 1 || skip[v] == 1)  continue;
        if(d[u] == INT_MAX || d[v] == INT_MAX || p[u] == p[v])  continue;
        if(ans > d[u] + w + d[v]) {
          ans = d[u] + w + d[v];
          a = p[u];
          b = p[v];
        }
      }
      return new Edge(a, b, ans);
    }

    public static void main(String[] args) throws IOException {
        Reader reader = new Reader();
        n = reader.nextInt();
        m = reader.nextInt();
        k = reader.nextInt();

        adj = (ArrayList<DirectedEdge>[]) new ArrayList[n + 2];
        for(int i = 0; i < n + 2; i++) {
          adj[i] = new ArrayList<DirectedEdge>();
        }

        E = new ArrayList<Edge>();

        int u, v, w;
        for(int i = 0; i < m; i++) {
          u = reader.nextInt();
          v = reader.nextInt();
          w = reader.nextInt();
          adj[u].add(new DirectedEdge(v, w));
          adj[v].add(new DirectedEdge(u, w));
          E.add(new Edge(u, v, w));
        }
        for(int i = 0; i < k; i++) {
          u = reader.nextInt();
          S[i] = u;
        }

        Edge tmp = run_nearest();

        int x1 = tmp.u, y1 = tmp.v, d1 = tmp.w;

        int c1 = -1, c2 = -1;

        run(x1);
        for(int i = 1; i <= n; i++) dx1[i] = d[i];
        run(y1);
        for(int i = 1; i <= n; i++) dy1[i] = d[i];

        for(int i = 0; i < k; i++) {
          int c = S[i];
          if(c == x1 || S[i] == y1)  continue;
          if(c1 == -1 || dy1[c] <= dy1[c1]) {
            c2 = c1;
            c1 = c;
          } else if(c2 == -1 || dy1[c] < dy1[c2]) {
            c2 = c;
          }
        }

        int ans = INT_MAX;

        if(dx1[x1] != INT_MAX && dy1[c1] != INT_MAX) {
          if(ans > dx1[c1] + dy1[c2]) {
            ans = dx1[c1] + dy1[c2];
          }
        }

        for(int i = 0; i < k; i++) {
          int x2 = S[i];
          if(x2 == x1 || x2 == y1 || x2 == c1)  continue;
          if(dx1[x2] != INT_MAX && dy1[c1] != INT_MAX) {
            if(ans > dx1[x2] + dy1[c1]) {
              ans = dx1[x2] + dy1[c1];
            }
          }
        }

        skip[x1] = skip[y1] = 1;
        tmp = run_nearest();
        int d2 = tmp.w;
        if(d1 != INT_MAX && d2 != INT_MAX) {
          if(ans > d1 + d2) {
            ans = d1 + d2;
          }
        }

        System.out.println(ans);
    }
}
