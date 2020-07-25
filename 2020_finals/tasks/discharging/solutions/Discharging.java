import java.io.*;
import java.util.*;

public class Discharging {
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

        public long nextLong() throws IOException
        {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');
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
    public static Vector<Double> intersect = new Vector<Double>();
    public static Vector<Long> grad = new Vector<Long>(),constant = new Vector<Long>();
    static boolean cmp(int a,int b,long g,long ct) {
        return (ct - constant.get(b))*(grad.get(a) - g) < (ct - constant.get(a))*(grad.get(b) - g);
    }
    public static double intersection(int a,long g,long ct){
        return ((double)constant.get(a)-(double)ct)/((double)g-(double)grad.get(a));
    }
    public static void popHull(){
        int a = constant.size()-1;
        constant.remove(a);
        grad.remove(a);
        intersect.remove(a);
    }
    public static void pushHull(double a,long b,long c){
        intersect.add(a);
        grad.add(b);
        constant.add(c);
    }
    public static void main(String[] args) throws IOException {
        Reader reader = new Reader();
        int N = reader.nextInt();
        long[] T = new long[N+1];
        for(int i = 1; i <= N; i++) {
            T[i] = reader.nextLong();
        }
        Vector<Long> dp = new Vector<Long>();
        dp.add(0L);
        pushHull(2e9,0l,0l);
        long curDpVal =0;
        long curMax = 0;
        int idx = 0;
        for(int i = 1; i <= N; i++){
            long curT = T[i];
            if(curT >= curMax){
                curMax = curT;
                while(intersect.get(idx)<(double)curMax)idx++;
                curDpVal = N*curMax + grad.get(idx) * curMax + constant.get(idx);
            }
            dp.add(curDpVal);
            long g = -i;
            long ct = dp.get(i);
            while(intersect.size()-idx >= 2 && cmp(intersect.size()-2,intersect.size()-1,g,ct)){
                popHull();
            }
            intersect.set(intersect.size()-1, intersection(intersect.size()-1,g,ct));
            pushHull(2e9,g,ct);
        }
        System.out.print(dp.get(N));
        // write code here
    }
}
