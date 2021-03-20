import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.ByteOrder;

public class stub {
    private static final byte COMMAND_END = 0;
    private static final byte COMMAND_SETLIGHT = 1;
    private static final byte COMMAND_TAKEPATH = 2;
    
    private static BufferedInputStream reader;
    private static BufferedOutputStream writer;
    
    public static class RoomPathsPair {
        public int room;
        public int[] paths;
    }
    
    private static void readExact(BufferedInputStream reader, byte[] target) throws IOException {
        int count = target.length;
        int ret = count;
        int off = 0;
        while (count > 0) {
            int res = reader.read(target, off, count);
            if (res <= 0) throw new RuntimeException();
            count -= res;
            off += res;
        }
    }
    
    private static int readExactInt(BufferedInputStream reader) throws IOException {
        ByteBuffer buf = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN);
        readExact(reader, buf.array());
        return buf.getInt();
    }
    
    private static int[] readExactVector(BufferedInputStream reader) throws IOException {
        int len = readExactInt(reader);
        if (len == 0) return new int[0];
        ByteBuffer buf2 = ByteBuffer.allocate(4*len).order(ByteOrder.LITTLE_ENDIAN);
        readExact(reader, buf2.array());
        IntBuffer ib = buf2.asIntBuffer();
        int[] arr = new int[ib.remaining()];
        ib.get(arr);
        return arr;
    }
    
    private static void writeInt(BufferedOutputStream writer, int val) throws IOException {
        ByteBuffer buf = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN);
        buf.putInt(val);
        writer.write(buf.array());
    }
    
    public static RoomPathsPair take_path(int corridor) {
        try {
            writer.write(COMMAND_TAKEPATH);
            writeInt(writer, corridor);
            writer.flush();
            RoomPathsPair ret = new RoomPathsPair();
            ret.room = readExactInt(reader);
            ret.paths = readExactVector(reader);
            return ret;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    
    public static void set_light(int level) {
        try {
            writer.write(COMMAND_SETLIGHT);
            writeInt(writer, level);
            writer.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    
    public static void main(String[] args) throws IOException {
        System.in.close();
        System.out.close();
        System.err.close();
        reader = new BufferedInputStream(new FileInputStream(args[0]));
        writer = new BufferedOutputStream(new FileOutputStream(args[1]));
        while (true) {
            try {
                int N = readExactInt(reader);
                int K = readExactInt(reader);
                int L = readExactInt(reader);
                int[] parent = new int[N];
                ByteBuffer buf2 = ByteBuffer.allocate(4*N).order(ByteOrder.LITTLE_ENDIAN);
                readExact(reader, buf2.array());
                IntBuffer ib = buf2.asIntBuffer();
                ib.get(parent);
                int initial_level = readExactInt(reader);
                int[] paths = readExactVector(reader);
                (new Archaeologist()).archaeologist(N, K, L, parent, initial_level, paths);
                writer.write(COMMAND_END);
                writer.flush();
            } catch (RuntimeException e) {
                break;
            }
        }
    }
}
