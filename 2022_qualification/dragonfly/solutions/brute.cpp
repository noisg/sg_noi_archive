#include <bits/stdc++.h>
// brute
using namespace std;
const int n_max = 3e6 + 10;
vector<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[n_max];

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
    set<int> eaten; // a set to keep track of all the bugs eaten
    while(x) {
        // brute: simply walk up the tree
        if(bugs[x]) {
            eaten.insert(species[x]);
            bugs[x]--;
        }
        x = parent[x];
    }
    return eaten.size();
}


int main() {
    int n, d; cin>>n>>d;
    for(int i=1; i<=n; i++) {
        cin>>bugs[i];
    }
    for(int i=1; i<=n; i++) {
        cin>>species[i];
    }
    for(int i=1; i<=d; i++) {
        cin>>home[i];
    }
    for(int i=1; i<=n; i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    for(int i=1; i<=d; i++) {
        cout << query(home[i]) << " ";
    }
    cout << "\n";
    return 0;
}
