import java.util.ArrayList;
public class Archaeologist {
    public static int dfs(ArrayList<Integer>[] children, int[] weight, int index) {
        if (children[index].isEmpty()) {
            return weight[index] = 1;
        }
        int ct = 0;
        for (int x : children[index]) {
            ct += dfs(children, weight, x);
        }
        return weight[index] = ct;
    }
    public void archaeologist(int N, int K, int L, int[] map, int lightlevel, int[] paths) {
        ArrayList<Integer>[] children = (ArrayList<Integer>[]) new ArrayList[N];
        for (int i=0;i<N;++i) children[i] = new ArrayList<Integer>();
        for(int i=1;i<N;++i) children[map[i]].add(i);
        int[] weight = new int[N];
        dfs(children, weight, 0);
        int curr = 0;
        int currlight = lightlevel;
        int[] currpaths = paths;
        int depth = 0;
        while (!children[curr].isEmpty()) {
            int estimate = 0;
            boolean has_zero = false;
            for (int y : currpaths) {
                if (y == 0) {
                    has_zero = true;
                    break;
                }
            }
            if (has_zero) {
                for(int x : children[curr]) {
                    estimate += Math.min(weight[x], depth + 1);
                }
                for(int y : currpaths) {
                    if (y != 0) --estimate;
                }
            }
            else {
                for(int y : currpaths) {
                    estimate += L - y;
                }
            }
            if (estimate <= depth) {
                --estimate;
                estimate = L - estimate;
                if (currlight != estimate) stub.set_light(estimate);
            }
            int minitem = 0;
            for (int i=1;i<currpaths.length; ++i) {
                if (currpaths[i] < currpaths[minitem]) minitem = i;
            }
            stub.RoomPathsPair pr = stub.take_path(minitem);
            curr = pr.room;
            currlight = currpaths[minitem];
            currpaths = pr.paths;
            ++depth;
        }
        stub.set_light(L);
    }
}
