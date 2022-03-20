#include <bits/stdc++.h>
// small-b
using namespace std;
const int n_max = 2e6 + 10;
vector<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[n_max];
bitset<n_max> eaten;

// assign parents
void dfs(int x) {
    for(int i: adj[x]) {
        if(i != parent[x]) {
            parent[i] = x;
            dfs(i);
        }
    }
}

int query(int x) {
    vector<int> visited;
    int ans = 0;
    vector<int> v;
    while(x) {
        // brute: simply walk up the tree
        if(bugs[x]) {
            for(int i: visited) {
                parent[i] = x;
            }
            visited.clear();
            if(!eaten[species[x]]) {
                ans++;
                eaten[species[x]] = true;
                v.push_back(species[x]);
            }
            bugs[x]--;
        } else {
            visited.push_back(x);
        }
        x = parent[x];
    }
    for(int i: v) {
        eaten[i] = false;
    }
    return ans;
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    for(int i=1; i<=n; i++) {
        scanf("%d", &bugs[i]);
        assert(bugs[i] <= 10);
    }
    for(int i=1; i<=n; i++) {
        scanf("%d", &species[i]);
    }
    for(int i=1; i<=d; i++) {
        scanf("%d", &home[i]);
    }
    for(int i=1; i<=n; i++) {
        int u,v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    for(int i=1; i<=d; i++) {
        printf("%d ", query(home[i]));
    }
    printf("\n");
    return 0;
}
