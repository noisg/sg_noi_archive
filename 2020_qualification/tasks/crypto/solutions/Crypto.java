import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;

public class Crypto {
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
        int[] P = new int[N + 1];
        int[] P2 = new int[N + 1];
        long[] F = new long[N];
        long ANS = 1;
        final long MOD = 1000000007;
        for(int a = 1; a <= N; ++a) {
            P[a] = reader.nextInt();
            P2[a] = P[a];
        }
        Arrays.sort(P2, 1, N + 1);
        for (int a = 1; a <= N; ++a)
            P[a] = Arrays.binarySearch(P2, 1, N + 1, P[a]);
        F[0] = 1;
        for (int a = 1; a < N; ++a) {
            F[a] = F[a - 1] * a;
            F[a] %= MOD;
        }
        int[] FT = new int[N + 1];
        for (int a = 1; a <= N; ++a) {
            FT[a] += 1;
            int b = a + (a & -a);
            if (b <= N) FT[b] += FT[a];
        }
        for (int a = 1; a <= N; ++a) {
            int order = 0;
            for (int x = P[a]; x != 0; x -= x & -x) order += FT[x];
            ANS += (order - 1) * F[N - a];
            ANS %= MOD;
            for (int x = P[a]; x <= N; x += x & -x) --FT[x];
        }
        System.out.println(ANS);
    }
}
