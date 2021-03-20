import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class stub {
    private static int N, K, L;
    private static ArrayList<Integer>[] adjlist;
    private static int archaeologist_index;
    private static int archaeologist_room;
    private static int[] levels;
    private static boolean[] explored;
    
    public static class RoomPathsPair {
        public int room;
        public int[] paths;
    }

    private static int[] prep_paths(int room) {
        ArrayList<Integer> currlist = adjlist[room];
        Collections.shuffle(currlist);
        int[] ret = new int[currlist.size()];
        for (int i=0;i<ret.length; ++i) {
            ret[i] = levels[currlist.get(i)];
        }
        return ret;
    }
    
    public static RoomPathsPair take_path(int corridor) {
        if (!(0 <= corridor && corridor < adjlist[archaeologist_room].size())) {
            System.out.println("take_path() called with invalid corridor");
            System.exit(1);
        }
        archaeologist_room = adjlist[archaeologist_room].get(corridor);
        System.out.println("Taking corridor " + corridor + " to room " + archaeologist_room);
        int[] paths = prep_paths(archaeologist_room);
        explored[archaeologist_room] = true;
        RoomPathsPair ret = new RoomPathsPair();
        ret.room = archaeologist_room;
        ret.paths = paths;
        return ret;
    }
    
    public static void set_light(int level) {
        if (!(0 <= level && level <= L)) {
            System.out.println("set_light() called with invalid level");
            System.exit(1);
        }
        System.out.println("Setting light at " + archaeologist_room + " to " + level);
        levels[archaeologist_room] = level;
    }
    
    @SuppressWarnings({"rawtypes", "unchecked"})
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        K = sc.nextInt();
        L = sc.nextInt();
        adjlist = (ArrayList<Integer>[]) new ArrayList[N];
        for (int i=0;i<N;++i) adjlist[i] = new ArrayList<Integer>();
        levels = new int[N];
        explored = new boolean[N];
        int[] parent = new int[N];
        parent[0] = -1;
        for (int i = 1; i < N; ++i) {
            parent[i] = sc.nextInt();
            adjlist[parent[i]].add(i);
        }
        for (int i = 0; i < K; ++i) {
            System.out.println("Archaeologist " + i + ":");
            archaeologist_index = i;
            archaeologist_room = 0;
            int[] paths = prep_paths(0);
            explored[0] = true;
            (new Archaeologist()).archaeologist(N, K, L, parent, levels[0], paths);
        }
        boolean all_explored = true;
        for (boolean b : explored) {
            if (!b) {
                all_explored = false;
                break;
            }
        }
        if (!all_explored) {
            System.out.println("Not all rooms were explored");
            System.exit(1);
        }
        System.out.println("All rooms explored successfully");
    }
}
