#include <bits/stdc++.h>
// dnc-level
using namespace std;


const int n_max = 3e6 + 10;

list<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[n_max];
int home2[n_max];
int query_count[n_max];
int death_time[n_max];
int postorder[n_max];

int preorder_counter = 0;
int postorder_counter = 0;
pair<int,int> preorder_interval[n_max];

void dfs(int x) {
    preorder_interval[x].first = preorder_counter;
    preorder_counter++;
    for(int i: adj[x]) {
        if(i != parent[x]) {
            parent[i] = x;
            dfs(i);
            query_count[x] += query_count[i];
        }
    }
    postorder[postorder_counter] = x;
    postorder_counter++;
    preorder_interval[x].second = preorder_counter;
}

bitset<n_max> alive;
int other_parent[n_max];
void brute(int level, int d) {
    for(int i=1; i<=d; i++) {
        int x = home[i];
        while(x) {
            if(bugs[x]) {
                bugs[x]--;
                if(bugs[x]==0) {
                    death_time[x] += i%level;
                }
            }
            x = parent[x];
        }
    }
}

void dnc(int level, int d, int n) { // level is a power of 2
    if(level==0) return;
    int* vs = postorder;
    int* ve = postorder + n;
    memset(query_count, 0, (n+3)*sizeof(int));
    for(int i=1; i<=d; i++) {
        if((i&level)==0) {
            query_count[home[i]]++;
        }
    }
    for(int* p = vs; p < ve; p++) {
        query_count[parent[*p]] += query_count[*p];
    }
    alive.reset();
    for(int i=1; i<=n; i++) {
        if(query_count[i] < bugs[i]) {
            alive[i] = true;
            bugs[i] -= query_count[i];
            death_time[i] |= level;
        }
    }

    for(int* p = ve-1; p>=vs; p--) {
        if(alive[parent[*p]] ^ alive[*p]) {
            other_parent[*p] = parent[*p];
            parent[*p] = other_parent[other_parent[*p]];
        } else {
            other_parent[*p] = other_parent[parent[*p]];
        }
    }

    for(int i=1; i<=d; i++) {
        if(i&level) {
            if(!alive[home[i]]) {
                home[i] = other_parent[home[i]];
            }
        } else {
            if(alive[home[i]]) {
                home[i] = other_parent[home[i]];
            }
        }
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

bool species_root[n_max];
list<int> species_child[n_max];
int dfs_stack[n_max];

void get_species_child(int x) {
    int t = species[x];
    if(dfs_stack[t] != -1) {
        species_child[dfs_stack[t]].push_back(x);
        species_root[x] = false;
    }
    int prev = dfs_stack[t];
    dfs_stack[t] = x;

    for(int i: adj[x]) {
        if(i != parent[x]) {
            get_species_child(i);
        }
    }
    dfs_stack[t] = prev;
}

int counter[n_max];

bool is_active[n_max];

int time_global = 0;


struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree(int _n) {
        n = _n;
        bit.assign(n, 0);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

FenwickTree fw(n_max);

void activate(int x) {
    assert(!is_active[x]);
    if(death_time[x] > time_global) { // then we should activate it
        fw.add(preorder_interval[x].first, 1);
        fw.add(preorder_interval[x].second, -1);
        is_active[x] = true;
    } else {
        for(int i: species_child[x]) {
            if(i != parent[x]) {
                parent[i] = x;
                activate(i);
            }
        }
    }
}

void deactivate(int x) {
    if(!is_active[x]) {
        return;
    }
    // activate all children
    fw.add(preorder_interval[x].first, -1);
    fw.add(preorder_interval[x].second, 1);
    for(int i: species_child[x]) {
        if(i != parent[x]) {
            activate(i);
        }
    }

}


int main() {
    int n,d;
    fastscan(n);
    fastscan(d);
    for(int i=1; i<=n; i++) {
        fastscan(bugs[i]);
        //death_time[i] = d+1;
    }
    for(int i=1; i<=n; i++) {
        fastscan(species[i]);
    }
    for(int i=1; i<=d; i++) {
        fastscan(home[i]);
        home2[i] = home[i];
    }
    for(int i=1; i<n; i++) {
        int u,v;
        fastscan(u);
        fastscan(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preorder_counter = 0;
    dfs(1);
    int level_low = 1;
    for(int i=1<<(__lg(d)); i>=level_low; i/=2) {
        dnc(i, d, n);
    }

    for(int i=1; i<=n; i++) {
        species_root[i] = true;
    }
    for(int i=1; i<=n; i++) {
        dfs_stack[i] = -1;
    }
    preorder_counter = 0;
    postorder_counter = 0;
    dfs(1);
    get_species_child(1);

    for(int i=1; i<=n; i++) {
        if(species_root[i]) {
            activate(i);
        }
    }

    vector<int> die_order(n);
    for(int i=1; i<=n; i++) {
        die_order[i-1] = i;
    }

    sort(die_order.begin(), die_order.end(), [](int a1, int a2){return death_time[a1] < death_time[a2];});
    auto pt = die_order.begin();
    while(pt != die_order.end() && death_time[*pt] == 0) {
        deactivate(*pt);
        is_active[*pt] = false;
        pt++;
    }
    for(int i=1; i<=d; i++) {
        int z = preorder_interval[home2[i]].first;
        printf("%d ", fw.sum(z));
        time_global++;
        while(pt != die_order.end() && death_time[*pt] == i) {
            deactivate(*pt);
            is_active[*pt] = false;
            pt++;
        }
    }
    printf("\n");
}
