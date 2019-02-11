import java.io.IOException;
import java.io.InputStream;
import java.util.InputMismatchException;

public class grader {

    private static int T;
    private static int N, Q, X1, X2, Y1, Y2, q;

    public static boolean inside_shape(int X, int Y) {
        q++;
        if(q > Q) {
            System.err.println("Wrong Answer. Used too many queries.");
            System.exit(0);
        }

        if(X <= 0 || X > N || Y <= 0 || Y > N) {
            System.err.print("Wrong Answer. Query parameters out of range.");
            System.exit(0);
        }

        return (X >= X1 && X <= X2 && Y >= Y1 && Y <= Y2);
    }

    public static void main(String[] args) throws IOException {
        squarerect solver = new squarerect();
        InputReader inputReader = new InputReader(System.in);
        T = inputReader.readInt();
        N = inputReader.readInt();
        Q = inputReader.readInt();
        int mxq = 0;
        for (int i = 0; i < T; i++) {
            X1 = inputReader.readInt();
            Y1 = inputReader.readInt();
            X2 = inputReader.readInt();
            Y2 = inputReader.readInt();
            q = 0;
            boolean user_ans = solver.am_i_square(N, Q);
            boolean act_ans = (Y2 - Y1) == (X2 - X1);
            if (user_ans != act_ans) {
                System.err.println("Wrong Answer.");
                System.exit(0);
            }
            if (q > mxq){
                mxq = q;
            }
        }
        System.out.printf("Correct. Used %d out of %d queries.\n", mxq, Q);
        System.out.close();
    }
}

class InputReader {
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;

    public InputReader(InputStream stream) {
        this.stream = stream;
    }

    public int read() {
        if (numChars == -1) {
            throw new InputMismatchException();
        }
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0) {
                return -1;
            }
        }
        return buf[curChar++];
    }

    public int readInt() {
        int c = eatWhite();
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int res = 0;
        do {
            if (c < '0' || c > '9') {
                throw new InputMismatchException();
            }
            res *= 10;
            res += c - '0';
            c = read();
        } while (!isSpaceChar(c));
        return res * sgn;
    }

    public String readString() {
        int c = eatWhite();
        StringBuilder res = new StringBuilder();
        do {
            if (Character.isValidCodePoint(c))
                res.appendCodePoint(c);
            c = read();
        } while (!isSpaceChar(c));
        return res.toString();
    }

    private int eatWhite() {
        int c = read();
        while (isSpaceChar(c)) {
            c = read();
        }
        return c;
    }

    public static boolean isSpaceChar(int c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }
}
