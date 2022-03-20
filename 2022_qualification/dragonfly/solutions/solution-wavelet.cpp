#include <bits/stdc++.h>

using namespace std;


const int n_max = 3e6 + 10;

int counter = 0;

vector<int> die_order;
int death_time[n_max];

pair<int,int> path_index[n_max];
vector<int> path[n_max];

list<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[n_max];
vector<int> query[n_max];
vector<int> preorder;

pair<int,int> preorder_interval[n_max];
pair<int,int> wavelet_interval[n_max];
int wavelet_counter = 1;
int preorder_counter = 0;
int wavelet_query[n_max];
// assign parents
void dfs(int x) {
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
}

int b_base[n_max*23];
int* b_ptr = b_base;

int* b[1<<22];

void build_node(int idx, int *from, int *to, int x, int y) {

    if(x == y or from >= to) return;
    int mid = (x + y)/2;
    auto f = [mid](int x){
        return x <= mid;
    };
    b[idx] = b_ptr;
    b_ptr += (to-from+1);
    int* pt = b[idx];
    *pt = 0;
    for(auto it = from; it != to; it++) {
        *(pt+1) = (*pt) + f(*it);
        pt++;
    }
    //see how lambda function is used here
    auto pivot = stable_partition(from, to, f);
    build_node(idx*2, from, pivot, x, mid);
    build_node(idx*2+1, pivot, to, mid+1, y);
}

int kth(int idx, int l, int r, int k, int lo, int hi) {
    if(lo == hi) return lo;
    int inLeft = b[idx][r] - b[idx][l-1];
    int lb = b[idx][l-1]; //amt of nos in first (l-1) nos that go in left
    int rb = b[idx][r]; //amt of nos in first (r) nos that go in left
    int mid = (lo+hi)/2;
    if(k <= inLeft) return kth(idx*2, lb+1, rb , k, lo, mid);
    return kth(idx*2+1, l-lb, r-rb, k-inLeft, mid+1, hi);
}

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
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
    build_node(1, wavelet_query+1, wavelet_query+d+1, 1, d+1);

    for(int i=1; i<=n; i++) {
        if(bugs[i]==0) {
            death_time[i] = 0;
        } else if(wavelet_interval[i].second - wavelet_interval[i].first >= bugs[i]) {
            death_time[i] = kth(1, wavelet_interval[i].first, wavelet_interval[i].second-1, bugs[i], 1, d+1);
        } else {
            death_time[i] = d+1;
        }
    }
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


char buff[22];
char* buff_ptr = buff+19;
void fastscan(int &number) {
    scanf("%d", &number);
}


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
    for(int i=0; i<n; i++) {
        die_order[i] = i+1;
    }
    assert(preorder_counter==n);
    sort(die_order.begin(), die_order.end(),
         [](int a, int b) {return death_time[a] < death_time[b];});

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
}
