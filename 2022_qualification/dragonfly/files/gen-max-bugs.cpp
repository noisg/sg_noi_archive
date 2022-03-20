#include "testlib.h"

using namespace std;

vector<pair<int,int>> generate_random_tree(int n, int k) {
    vector<pair<int,int>> result;
    if(k==0) {

        vector<int> parent(n+1);
        for(int i=1; i<=n; i++) parent[i] = i;
        int connections = 0;
        while(connections < n-1) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            int x_p = x;
            int y_p = y;
            while(x_p != parent[x_p]) {
                x_p = parent[x_p] = parent[parent[x_p]];
            }
            while(y_p != parent[y_p]) {
                y_p = parent[y_p] = parent[parent[y_p]];
            }
            if(x_p != y_p) {
                connections++;
                result.push_back(make_pair(x,y));
                parent[x_p] = y_p;
            }
        }
    } else {
        for(int i=2; i<=n; i++) {
            result.push_back(make_pair(i, rnd.next(max(i-k,1), i-1)));
        }
        return result;
    }
    return result;

}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int d = atoi(argv[2]);
    int k =atoi(argv[3]);
    printf("%d %d\n", n, d);
    // number of bugs
    for(int i=1; i<=n; i++) {
        if(i>1) printf(" ");
        printf("%d", d);
    }
    printf("\n");
    // species type
    for(int i=1; i<=n; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(1, n));
    }
    printf("\n");
    // home of dragonfly
    for(int i=1; i<=d; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(2, n));
    }
    printf("\n");
    vector<pair<int,int>> g = generate_random_tree(n, k);
    for(pair<int,int> p: g) {
        printf("%d %d\n", p.first, p.second);
    }
}
