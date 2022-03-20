#include "testlib.h"

using namespace std;


// parent of i is uniformly chosen from i-k, i-k+1, ..., i-1
// large values of k generate shallow trees, higher branching
// small values of k generate more "linear" trees
vector<pair<int,int>> generate_random_tree(int n, int k) {
    vector<pair<int,int>> result;
    for(int i=2; i<=n; i++) {
        result.push_back(make_pair(i, rnd.next(max(i-k,1), i-1)));
    }
    return result;

}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int d = atoi(argv[2]);
    int k = atoi(argv[3]);
    ensure(k>=1);
    printf("%d %d\n", n, d);
    // number of bugs
    for(int i=1; i<=n; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(1, min(d,(int)1e6)));
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
