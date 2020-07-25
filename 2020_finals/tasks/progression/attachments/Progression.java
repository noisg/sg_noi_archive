import java.io.DataInputStream;
import java.io.IOException;

public class Progression {
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

    public static void main(String[] args) throws IOException {
        Reader reader = new Reader();
        PrintStream out = new PrintStream(new BufferedOutputStream(System.out));
        
        int N = reader.nextInt(); // read an integer
        // read more integers...
        
        // write code here...
        
        int ans = 100;
        out.print(ans); // write an integer
        // write more integers and characters...
        
        out.flush(); // remember to flush just once, at the very end of your program
    }
}
