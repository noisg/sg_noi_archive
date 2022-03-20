#include "testlib.h"
#include <list>
using namespace std;

int l;
vector<pair<int,int>> generate_random_tree(int n) {
    vector<pair<int,int>> result;
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
    for(int i=0; i<=n; i++) {
        perm[i] = i;
    }
    shuffle(perm.begin()+2, perm.end());
    for(pair<int,int> &p: result) {
        p.first = perm[p.first];
        p.second = perm[p.second];
        ensure(p.first);
    }
    return result;
}

const int n_max = 3e6;
int par[n_max];
list<int> adj[n_max];
int q_count[n_max];

void dfs(int x) {
    for(int i: adj[x]) {
        if(i!=par[x]) {
            par[i] = x;
            dfs(i);
        }
    }
}
void dfs2(int x) {
    for(int i: adj[x]) {
        if(i!=par[x]) {
            dfs2(i);
            q_count[x] += q_count[i];
        }
    }
}
int home[n_max];

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int d = atoi(argv[2]);
    l = atoi(argv[3]);
    printf("%d %d\n", n, d);
    vector<pair<int,int>> g = generate_random_tree(n);
    for(auto p: g) {
        adj[p.first].push_back(p.second);
        adj[p.second].push_back(p.first);
    }
    dfs(1);
    vector<int> leaves;
    for(int i=1; i<=n; i++) {
        if(adj[i].size()==1 && i!=1) {
            leaves.push_back(i);
        }
    }
    for(int i=1; i<=d; i++) {
        if(rnd.next(0,1)) {
            home[i] = rnd.next(2, n);
        } else {
            int idx = rnd.next(1, (int)leaves.size());
            home[i] = leaves[idx-1];
        }
        q_count[home[i]]++;
    }
    dfs2(1);

    // number of bugs
    for(int i=1; i<=n; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(1, 1 + q_count[i]));
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

    for(pair<int,int> p: g) {
        printf("%d %d\n", p.first, p.second);
    }
}
