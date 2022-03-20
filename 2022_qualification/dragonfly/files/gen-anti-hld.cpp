#include "testlib.h"

using namespace std;


vector<pair<int,int>> generate_random_tree(int n) {
    vector<pair<int,int>> result;
    int l = 9;
    int k = n/(l+2);
    int k0 = k;
    for(int i=2; i<k0; i++) {
        // put an edge between i and i/2
        // but we sub-divide it some number of times
        // use 6 new numbers
        result.emplace_back(i, k);
        for(int j=0; j<l; j++) {
            result.emplace_back(k, k+1);
            k++;
        }
        result.emplace_back(k, i/2);
        k++;
    }
    ensure(k <= n);
    while(k<=n) {
        result.emplace_back(k, rnd.next(1, k-1));
        k++;
    }
    ensure(result.size() == n-1);
    shuffle(result.begin(), result.end());
    vector<int> perm(n+1);
    for(int i=1; i<=n; i++) {
        perm[i] = i;
    }
    for(pair<int,int> &p: result) {
        p.first = perm[p.first];
        p.second = perm[p.second];
        ensure(p.first);
    }
    return result;

}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int d = atoi(argv[2]);
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

    vector<pair<int,int>> g = generate_random_tree(n);
    for(pair<int,int> p: g) {
        printf("%d %d\n", p.first, p.second);
    }
}
