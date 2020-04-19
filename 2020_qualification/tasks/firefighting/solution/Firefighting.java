import java.io.DataInputStream;
import java.io.IOException;
import java.util.*;
import java.io.*;

public class Firefighting {
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
    
    public static class DirectedEdge{
        int target;
        int len;
        public DirectedEdge(int target, int len){
            this.target=target;
            this.len=len;
        }
    }
    public static class Result{
        boolean type;
        long val;
        public Result(boolean type, long val){
            this.type=type;
            this.val=val;
        }
    }
    
    public static ArrayList<DirectedEdge>[] adjlist;
    public static ArrayList<Integer> ans;
    public static long K;
    
    public static Result dfs(int index, int prev, long dist){
        long max_overflow = Long.MIN_VALUE;
        long max_underflow = 0;
        for(DirectedEdge e : adjlist[index]){
            if(e.target != prev){
                Result res = dfs(e.target, index, e.len);
                if(res.type){
                    if(max_overflow < res.val) max_overflow = res.val;
                }
                else {
                    if(max_underflow < res.val) max_underflow = res.val;
                }
            }
        }
        Result ret;
        if(max_overflow >= max_underflow) {
            ret = new Result(true, max_overflow-dist);
        }
        else {
            ret = new Result(false, max_underflow+dist);
        }
        if(!ret.type && ret.val > K){
            ans.add(index);
            ret.type = true;
            ret.val = K-dist;
        }
        if(ret.type && ret.val < 0){
            ret.type = false;
            ret.val = 0;
        }
        return ret;
    }

    public static void main(String[] args) throws IOException {
        Reader reader = new Reader();
        PrintStream out = new PrintStream(new BufferedOutputStream(System.out));
        int N = reader.nextInt();
        K = reader.nextLong();
        adjlist = (ArrayList<DirectedEdge>[]) new ArrayList[N];
        ans = new ArrayList<Integer>();
        for(int i=0;i<N;++i){
            adjlist[i] = new ArrayList<DirectedEdge>();
        }
        for(int i=1;i<N;++i){
            int A = reader.nextInt();
            int B = reader.nextInt();
            int W = reader.nextInt();
            --A;--B;
            adjlist[A].add(new DirectedEdge(B,W));
            adjlist[B].add(new DirectedEdge(A,W));
        }
        dfs(0, -1, Long.MAX_VALUE >> 2);
        out.println(ans.size());
        for(int x : ans){
            out.print(x+1);
            out.print(' ');
        }
        out.flush();
    }
}
