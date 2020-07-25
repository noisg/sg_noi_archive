import java.io.DataInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.io.BufferedOutputStream;

public class Progression {
    private static class Reader {
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
            boolean flip = false;
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
        public long nextLong() throws IOException {
            long ret = 0;
            boolean flip = false;
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
    
    private static class Node {
        long left_s, left_c, right_s, right_c;
        int left_len, right_len, curr_len;
        boolean is_override;
        long push_s, push_c;
    }
    
    private static final int DEPTH = 19;
    private static Node[] stree = new Node[1<<(DEPTH+1)];
    private static void construct(int i) {
        final Node me = stree[i], left = stree[i<<1], right = stree[(i<<1)+1];
        final int mylen = 1<<(Integer.numberOfLeadingZeros(i)-(31-DEPTH));
        final int childlen = mylen>>1;
        
        if(childlen==1) {
            right.right_c=left.left_c=right.left_c=left.right_c=right.left_s-left.right_s;
        }
        me.curr_len=Math.max(left.curr_len,right.curr_len);
        int lmergelen =
            (right.left_s - left.right_s == left.right_c)
                ? ((right.left_c == left.right_c) ? right.left_len : 1)
                : 0;
        int rmergelen =
            (right.left_s - left.right_s == right.left_c)
                ? ((right.left_c == left.right_c) ? left.right_len : 1)
                : 0;
        me.curr_len = Math.max(me.curr_len, Math.max(left.right_len + lmergelen, right.left_len + rmergelen));
        me.left_s = left.left_s;
        me.left_c = left.left_c;
        if(left.left_len == childlen) me.left_len = childlen + lmergelen;
        else me.left_len = left.left_len;
        me.right_s = right.right_s;
        me.right_c = right.right_c;
        if(right.right_len == childlen) me.right_len = childlen + rmergelen;
        else me.right_len = right.right_len;
    }
    private static void pushdown(int i){
        final Node me = stree[i];
        if(me.is_override||me.push_s!=0||me.push_c!=0){
            Node left=stree[i<<1];
            Node right=stree[(i<<1)+1];
            final int mylen = 1 << (Integer.numberOfLeadingZeros(i) - (31 - DEPTH));
            final int childlen = mylen >> 1;

            if(me.is_override){
                me.is_override=false;
                left.curr_len=childlen;
                left.left_s=me.push_s;
                left.left_c=me.push_c;
                left.left_len=childlen;
                left.right_s=me.push_s+me.push_c*(childlen-1);
                left.right_c=me.push_c;
                left.right_len=childlen;
                left.push_s=me.push_s;
                left.push_c=me.push_c;
                left.is_override=true;
                final long tmp_s=me.push_s+me.push_c*childlen;
                right.curr_len=childlen;
                right.left_s=tmp_s;
                right.left_c=me.push_c;
                right.left_len=childlen;
                right.right_s=tmp_s+me.push_c*(childlen-1);
                right.right_c=me.push_c;
                right.right_len=childlen;
                right.push_s=tmp_s;
                right.push_c=me.push_c;
                right.is_override=true;
            }
            else{
                left.left_s+=me.push_s;
                left.left_c+=me.push_c;
                left.right_s+=me.push_s+me.push_c*(childlen-1);
                left.right_c+=me.push_c;
                left.push_s+=me.push_s;
                left.push_c+=me.push_c;
                final long tmp_s=me.push_s+me.push_c*childlen;
                right.left_s+=tmp_s;
                right.left_c+=me.push_c;
                right.right_s+=tmp_s+me.push_c*(childlen-1);
                right.right_c+=me.push_c;
                right.push_s+=tmp_s;
                right.push_c+=me.push_c;
            }
            me.push_s=0;
            me.push_c=0;
        }
    }
    private static void increment(int i, int l, int r, long s, int c){
        final Node me = stree[i];
        final int mylen = 1 << (Integer.numberOfLeadingZeros(i) - (31 - DEPTH));
        final int childlen = mylen >> 1;

        if(l==0&&r==mylen) {
            me.left_s += s;
            me.left_c += c;
            me.right_s += s + (long)(c) * (mylen - 1);
            me.right_c += c;
            me.push_s += s;
            me.push_c += c;
            return;
        }
        pushdown(i);
        if (l<childlen) increment(i<<1, l, Math.min(r,childlen), s, c);
        if (r>childlen) increment((i<<1)+1, Math.max(l-childlen,0), r-childlen, s+(long)(c)*Math.max(childlen - l, 0), c);
        construct(i);
    }
    private static void overwrite(int i, int l, int r, long s, int c){
        final Node me = stree[i];
        final int mylen = 1 << (Integer.numberOfLeadingZeros(i) - (31 - DEPTH));
        final int childlen = mylen >> 1;

        if(l==0&&r==mylen) {
            me.curr_len = mylen;
            me.left_s = s;
            me.left_c = c;
            me.left_len = mylen;
            me.right_s = s + (long)(c) * (mylen - 1);
            me.right_c = c;
            me.right_len = mylen;
            me.push_s = s;
            me.push_c = c;
            me.is_override = true;
            return;
        }
        pushdown(i);
        if (l<childlen) overwrite(i<<1, l, Math.min(r,childlen), s, c);
        if (r>childlen) overwrite((i<<1)+1, Math.max(l-childlen,0), r-childlen, s+(long)(c)*Math.max(childlen - l, 0), c);
        construct(i);
    }
    private static int query(int i, int l, int r){
        final Node me = stree[i];
        final int mylen = 1 << (Integer.numberOfLeadingZeros(i) - (31 - DEPTH));
        final int childlen = mylen >> 1;

        if(l==0&&r==mylen) {
            return me.curr_len;
        }
        final Node left=stree[i<<1];
        final Node right=stree[(i<<1)+1];
        pushdown(i);
        int ans = 0;
        if (l<childlen) ans = Math.max(ans, query(i<<1, l, Math.min(r,childlen)));
        if (r>childlen) ans = Math.max(ans, query((i<<1)+1, Math.max(l-childlen,0), r-childlen));
        if (l<childlen && r>childlen) {
            ans = Math.max(2, ans);
            int lmergelen =
                (right.left_s - left.right_s == left.right_c)
                    ? ((right.left_c == left.right_c) ? Math.min(r-childlen,right.left_len) : 1)
                    : 0;
            int rmergelen =
                (right.left_s - left.right_s == right.left_c)
                    ? ((right.left_c == left.right_c) ? Math.min(childlen-l,left.right_len) : 1)
                    : 0;
            ans = Math.max(ans, Math.max(Math.min(childlen-l,left.right_len) + lmergelen, Math.min(r-childlen,right.left_len) + rmergelen));
        }
        return ans;
    }

    public static void main(String[] args) throws IOException {
        for(int i=0;i<(1<<(DEPTH+1));++i)stree[i]=new Node();
        Reader reader = new Reader();
        PrintStream out = new PrintStream(new BufferedOutputStream(System.out));
        
        final int n = reader.nextInt();
        final int q = reader.nextInt();
        for (int i=0;i<n;++i){
            stree[(1 << DEPTH) + i].push_s = reader.nextInt();
        }
        for (int i=0;i<(1<<DEPTH);++i){
            stree[(1 << DEPTH) + i].is_override = true;
            stree[(1 << DEPTH) + i].curr_len = 1;
            stree[(1 << DEPTH) + i].left_s = stree[(1 << DEPTH) + i].push_s;
            stree[(1 << DEPTH) + i].left_len = 1;
            stree[(1 << DEPTH) + i].right_s = stree[(1 << DEPTH) + i].push_s;
            stree[(1 << DEPTH) + i].right_len = 1;
        }
        for(int i = (1<<DEPTH) - 1; i > 0; --i){
            construct(i);
        }
        for(int i=0;i<q;++i){
            final int type = reader.nextInt();
            if(type==1){
                final int l=reader.nextInt();
                final int r=reader.nextInt();
                final int s=reader.nextInt();
                final int c=reader.nextInt();
                increment(1, l-1, r, s, c);
            }
            else if(type==2){
                final int l=reader.nextInt();
                final int r=reader.nextInt();
                final int s=reader.nextInt();
                final int c=reader.nextInt();
                overwrite(1, l-1, r, s, c);
            }
            else if(type==3){
                final int l=reader.nextInt();
                final int r=reader.nextInt();
                out.print(query(1, l-1, r));
                out.print('\n');
            }
        }
        
        out.flush(); // remember to flush just once, at the very end of your program
    }
}
