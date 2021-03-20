import java.io.DataInputStream;
import java.io.IOException;
import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.lang.StringBuilder;

public class st4_java {
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
        int A[] = new int[N+1];
        int B[] = new int[N+1];
        for (int a = 0; a < N; ++a) A[a] = reader.nextInt();
        for (int a = 0; a < N; ++a) B[a] = reader.nextInt();
        double m_left = 1e9, m_right = 0;
        boolean can = true;
        for (int a = 0; a < N - 1 && can; ++a) {
            if ((A[a] <= A[a + 1]) && (B[a] <= B[a + 1])) can = false;
            else if (((A[a] >= A[a + 1]) && (B[a] > B[a + 1])) ||
                     ((A[a] > A[a + 1]) && (B[a] >= B[a + 1]))) continue;
            else {
                boolean right = (B[a] - B[a + 1]) > 0;
                double m = (double)(A[a + 1] - A[a]) / (double)(B[a] - B[a + 1]);
                if (right) m_right = Math.max(m_right, m);
                else m_left = Math.min(m_left, m);
            }
        }
        can &= m_left > m_right;
        out.write(can ? "YES\n" : "NO\n");
        out.flush();
    }
}