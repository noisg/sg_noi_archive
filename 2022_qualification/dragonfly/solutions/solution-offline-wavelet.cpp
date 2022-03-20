#include <bits/stdc++.h>

using namespace std;

const int n_max = 3e6 + 10;
const int d_max = 3e6+10;

vector<int> die_order;
int death_time[n_max];

pair<int,int> path_index[n_max];
vector<int> path[n_max];

list<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[d_max];
vector<int> query[n_max];
vector<int> preorder;

pair<int,int> preorder_interval[n_max];
pair<int,int> wavelet_interval[n_max];
int wavelet_counter = 1;
int preorder_counter = 0;
int wavelet_query[n_max];

int lt[n_max];
int rt[n_max];
int kt[n_max];

int w_query[n_max]; // each query holds 4 values, (idx, l, r, k)
// assign parents
void dfs(int x) {
    lt[x] = wavelet_counter;
    kt[x] = bugs[x];
    w_query[x] = x;
    wavelet_interval[x].first = wavelet_counter;
    preorder.push_back(x);
    preorder_interval[x].first = preorder_counter;
    preorder_counter++;
    for(int j: query[x]) {
        wavelet_query[wavelet_counter] = j; // put the timing there
        wavelet_counter++;
    }
    for(int i: adj[x]) {
        if(i != parent[x]) {
            parent[i] = x;
            dfs(i);
        }
    }
    preorder_interval[x].second = preorder_counter;
    wavelet_interval[x].second = wavelet_counter;
    rt[x] = wavelet_counter-1;
}

int b[d_max * 2];

void offline_wavelet(int *from, int *to, int x, int y, int *qs, int *qe) {
    if(qs == qe) return;
    if(y-x<=1) {
        while(qs<qe) {
            int z = *qs;
            if(rt[z]==1) {
                death_time[z] = *from;
            } else if(lt[z]==2) {
                death_time[z] = from[1];
            } else if(kt[z]==2) {
                death_time[z] = max(from[0], from[1]);
            } else {
                death_time[z] = min(from[0], from[1]);
            }
            qs++;
        }
        return;
    }
    if(from >= to) {
        for(int* p=qs; p<qe; p++) {
            death_time[*p] = *from;
        }
        return;
    }
    int mid = (x+y)/2;
    auto f = [mid](int z){
        return z <= mid;
    };
    int* pt = b;
    *pt = 0;
    for(auto it = from; it != to; it++) {
        *(pt+1) = (*pt) + f(*it);
        pt++;
    }
    auto pivot = stable_partition(from, to, f);

    int *p1 = qs;
    int* p2 = qe;
    while(p1 != p2) {
        int z = *p1;
        int lb = b[lt[z]-1];
        int rb = b[rt[z]];
        if(rb - lb >= kt[z]) {
            lt[z] = lb+1;
            rt[z] = rb;
            p1++;
        } else {
            lt[z] -= lb;
            rt[z] -= rb;
            kt[z] -= (rb-lb);
            p2--;
            swap(*p1, *p2);
        }
    }
    offline_wavelet(from, pivot, x, mid, qs, p1);
    offline_wavelet(pivot, to, mid+1, y, p1, qe);
}

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

void calculate_death_time(int d, int n)  {
    for(int i=1; i<=n; i++) {
        if(rt[i]+1-lt[i] < kt[i]) {
            death_time[i] = d+1;
        } else if (kt[i]==0) {
            death_time[i] = 0;
        }
    }
    auto pivot = partition(w_query+1, w_query+n+1, [](auto x) {return (rt[x] + 1 - lt[x] >= kt[x]) && (kt[x]>0);});
    offline_wavelet(wavelet_query+1, wavelet_query+d+1, 1, d, w_query+1, pivot);
}

bool species_root[n_max];
list<int> species_child[n_max];
int species_parent[n_max];
int dfs_stack[n_max];

void get_species_child(int x) {
    int t = species[x];
    assert(x);
    assert(dfs_stack[t] != 0);
    if(dfs_stack[t] != -1) {
        species_child[dfs_stack[t]].push_back(x);
        species_parent[x] = dfs_stack[t];
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

int time_global = 0;

bool is_active[n_max];

void activate(int x) {
    assert(!is_active[x]);
    if(death_time[x] > time_global) { // then we should activate it
        fw.add(preorder_interval[x].first, 1);
        fw.add(preorder_interval[x].second, -1);
        is_active[x] = true;
    } else {
        for(int i: species_child[x]) {
            if(i != parent[x]) {
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
    //s2.inc(preorder_interval[x].first, preorder_interval[x].second, -1);
    for(int i: species_child[x]) {
        if(i != parent[x]) {
            activate(i);
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

int counter[d_max];
int main() {
    int n,d;
    fastscan(n);
    fastscan(d);
    for(int i=1; i<=n; i++) {
        fastscan(bugs[i]);
        if(bugs[i]>d) bugs[i]=d;
        death_time[i] = d+1;
    }
    for(int i=1; i<=n; i++) {
        fastscan(species[i]);
    }
    for(int i=1; i<=d; i++) {
        fastscan(home[i]);
        query[home[i]].push_back(i);
    }
    for(int i=1; i<n; i++) {
        int u,v;
        fastscan(u);
        fastscan(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    calculate_death_time(d, n);


    for(int i=1; i<=n; i++) {
        species_root[i] = true;
    }
    for(int i=1; i<=n; i++) {
        dfs_stack[i] = -1;
    }
    get_species_child(1);

    for(int i=1; i<=n; i++) {
        if(species_root[i]) {
            activate(i);
        }
    }
    die_order = vector<int>(n);

    assert(preorder_counter==n);
    for(int i=1; i<=n; i++) {
        counter[death_time[i]]++;
    }
    for(int i=1; i<=d+1; i++) {
        counter[i] += counter[i-1];
    }
    for(int i=n; i>=1; i--) {
        counter[death_time[i]]--;
        die_order[counter[death_time[i]]] = i;
    }

    auto pt = die_order.begin();
    while(pt != die_order.end() && death_time[*pt] == 0) {
        deactivate(*pt);
        is_active[*pt] = false;
        pt++;
    }
    for(int i=1; i<=d; i++) {
        int z = preorder_interval[home[i]].first;
        printf("%d ", fw.sum(z));
        time_global++;
        while(pt != die_order.end() && death_time[*pt] == i) {
            deactivate(*pt);
            is_active[*pt] = false;
            pt++;
        }
    }
    printf("\n");
    return 0;
}
