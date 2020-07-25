import java.io.DataInputStream;
import java.io.IOException;
import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.lang.StringBuilder;

public class Labels {
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
        int D[] = new int[N+1];
        int P[] = new int[N+1];
        int maxn = 0, minn = 0;
        for (int a = 0; a < N - 1; ++a) {
            D[a] = reader.nextInt();
            if (a>0) D[a] += D[a - 1];
            maxn = Math.max(maxn, D[a]);
            minn = Math.min(minn, D[a]);
        }
        if (maxn - minn != N - 1) {
            System.out.println("-1");
            System.exit(0);
        }
        P[0] = N - maxn;
        for (int a = 1; a < N; ++a) P[a] = P[0] + D[a - 1];
        for (int a = 0; a < N; ++a) {
            out.write(Integer.toString(P[a]));
            if (a == N - 1) out.write("\n");
            else out.write(" ");
        }
        out.flush();
    }
}
