#include <bits/stdc++.h>

using namespace std;


const int n_max = 3e6 + 10;

list<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[n_max];

bitset<n_max> species_seen;
int ans[n_max];
int curr = 0;

void dfs(int x) {
    bool is_new = !species_seen[species[x]];
    if(is_new) {
        species_seen[species[x]] = true;
        curr++;
    }
    ans[x] = curr;
    for(int i: adj[x]) {
        if(i != parent[x]) {
            parent[i] = x;
            dfs(i);
        }
    }
    if(is_new) {
        species_seen[species[x]] = false;
        curr--;
    }
}

void fastscan(int &number) {
    int c;
    number = 0;
    do {
        c = getchar();
    } while(c<=47 || c>=58);
    do {
        number = number * 10 + c - 48;
        c = getchar();
    } while(c>47 && c<58);
}


int main() {
    int n,d;
    fastscan(n);
    fastscan(d);
    for(int i=1; i<=n; i++) {
        fastscan(bugs[i]);
    }
    for(int i=1; i<=n; i++) {
        fastscan(species[i]);
    }
    for(int i=1; i<=d; i++) {
        fastscan(home[i]);
    }
    for(int i=1; i<n; i++) {
        int u,v;
        fastscan(u);
        fastscan(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);

    for(int i=1; i<=d; i++) {
        printf("%d ", ans[home[i]]);
    }
    printf("\n");
}
