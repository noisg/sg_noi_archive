import java.io.DataInputStream;
import java.io.IOException;
import java.util.*;
import java.io.*;
class Fenwick{
  private int data_[];
  public int query(int index){
    int ret=0;
    for(;index>0;index-=(index&-index)){
      ret+=data_[index];
    }
    return ret;
  }
  public void update(int index){
    for(++index;index<data_.length;index+=(index&-index)){
      ++data_[index];
    }
  }
  public Fenwick(int n){
    data_=new int[n+1];
  }
}
class Element{
  long height;
  int index;
}
public class Mountains {
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

    public static void main(String[] args) throws IOException {
        Reader reader = new Reader();
        int n = reader.nextInt();
        Fenwick fw=new Fenwick(n);
        Element[] arr = new Element[n];
        for(int i=0;i<n;++i){
          Element el = arr[i] = new Element();
          el.height = reader.nextLong();
          el.index = i;
        }
        Arrays.sort(arr, (x,y) -> Long.compare(x.height,y.height));
        long ans=0;
        for(int i=0;i<n;){
          final long val=arr[i].height;
          int j;
          for(j=i;j<n&&arr[j].height==val;++j){
            final int idx=arr[j].index;
            final int tmp=fw.query(idx);
            ans+=tmp*(long)(i-tmp);
          }
          for(;i<j;++i){
            final int idx=arr[i].index;
            fw.update(idx);
          }
        }
        System.out.println(ans);
    }
}