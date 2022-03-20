#include "testlib.h"
#include <list>
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
    int k = atoi(argv[2]);
    printf("%d\n", n);
    vector<pair<int,int>> g = generate_random_tree(n,k);
    
    for(pair<int,int> p: g) {
        printf("%d %d\n", p.first, p.second);
    }
}

