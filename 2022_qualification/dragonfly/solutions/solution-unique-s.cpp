#include <bits/stdc++.h>

using namespace std;


const int n_max = 3e6 + 10;
const int d_max = 3e6 + 10;
int t_base[n_max * 16];
int d_base[n_max * 16];
int favorite_child[n_max];

int* pt_t = t_base;
int* pt_d = d_base;

int counter = 0;

vector<int> die_order;
int death_time[n_max];

pair<int,int> path_index[n_max];
vector<int> path[n_max];

list<int> adj[n_max];
int parent[n_max];
int bugs[n_max];
int species[n_max];
int home[d_max];
int query_count[n_max];
vector<int> preorder;


struct segtree {
    int n;
    int n0;
    int n_bits;
    int *t,*d;
    segtree(int _n) {
        n0 = _n;
        // increase n to next power of 2
        n_bits = 32 - __builtin_clz(_n + 1);
        n = (1<<n_bits);
        assert(n);
        t = pt_t;
        d = pt_d;
        pt_t += 2*n; // reserve 2n memory
        pt_d += 2*n;
    }
    segtree() {}
    void apply(int p, int value) {
        assert(t);
        t[p] += value;
        if (p < n) d[p] += value;
    }

    void build(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
        }
    }

    /*void push(int p) {
        for (int s = n_bits; s > 0; --s) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = 0;
            }
        }
    }*/

    void inc(int l, int r, int value) { // includes l, excludes r
        counter++;
        assert(n);
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            assert(r>1);
            if (l&1) apply(l++, value);
            if (r&1) apply(--r, value);
        }

        build(l0);
        build(r0 - 1);
    }

    void point_update(int l, int value) {
        counter++;
        l += n;
        t[l] += value;
        assert(value>0);
        while (l > 1) {
            if(t[l/2] == t[l^1] + d[l/2]) {
                break;
            }
            t[l/2] = min(t[l], t[l^1]) + d[l/2];
            l >>= 1;
        }
    }

    /*int query(int l, int r) { // includes l, excludes r
        counter++;
        l += n, r += n;
        push(l);
        push(r - 1);
        int res = 2e9;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t[l++]);
            if (r&1) res = min(t[--r], res);
        }
        return res;
    }*/

    int point_query(int x) {
        x += n;
        int ans = t[x];
        while(x) {
            ans += d[x];
            x /= 2;
        }
        return ans;
    }

    int find_zero() {
        counter++;
        int node = 1;
        int lazy = 0;
        for(int i=0; i<n_bits; i++) {
            lazy += d[node];
            node *= 2;
            if(lazy + t[node]) node++;
        }
        int ans = node - (1<<n_bits);
        return ans;
    }

    void extract_zeros(int i, int j) {
        counter++;
        while(true) {
            int k = find_zero();

            if(k>=n0) break;
            die_order.push_back(path[j][k]);
            death_time[path[j][k]] = i;
            point_update(k, 2e9);
        }
    }

};

segtree s[n_max];

// assign parents
bitset<n_max> bx;
void dfs(int x) {
    assert(!bx[x]);
    bx[x] = true;
    preorder.push_back(x);
    favorite_child[x] = -1;
    int best_value = -1;
    for(int i: adj[x]) {
        if(i != parent[x]) {
            parent[i] = x;
            dfs(i);
            if(query_count[i] > best_value) {
                best_value = query_count[i];
                favorite_child[x] = i;
            }
            query_count[x] += query_count[i];
        }
    }
}

pair<int,int> preorder_interval[n_max];
int preorder_counter = 0;
void dfs3(int x) {
    preorder_interval[x].first = preorder_counter;
    preorder_counter++;
    for(int i: adj[x]) {
        if(i != parent[x]) {
            dfs3(i);
        }
    }
    preorder_interval[x].second = preorder_counter;
}

int occupied = 0;
void dfs2(int i) {
    assert(i);
    int path_counter = i;
    if(path_index[i].first != -1) {
        return;
    }
    int items = 0;
    while(i != -1) {
        path_index[i] = make_pair(path_counter, items);

        path[path_counter].push_back(i);
        items++;
        i = favorite_child[i];
    }
    s[path_counter] = segtree(items);
    int n0 = s[path_counter].n;
    for(int j=0; j<items; j++) {
        s[path_counter].t[j + n0] = bugs[path[path_counter][j]];
        if(bugs[path[path_counter][j]] == 0) {
            s[path_counter].t[j + n0] = 2e9;
        }
    }
    for(int j=n0-1; j>=1; j--) {
        s[path_counter].t[j] = min(s[path_counter].t[j*2], s[path_counter].t[j*2+1]);
    }
}

void calculate_death_time(int d, int n)  {
    // for each node, find out the time in which it dies, or maybe it survives forever
    // first, construct a HLD of the tree
    // put a segment tree over every path
    for(int i=1; i<=n; i++) {
        path_index[i].first = -1;
    }
    for(int i: preorder) {
        dfs2(i); // do in preorder to avoid complications for HLD
    }
    for(int i=1; i<=d; i++) {
        int h = home[i];
        while(h) {
            int j = path_index[h].first;
            //printf("j=%d\n", j);
            //printf("h=%d\n", h);
            s[j].inc(0, path_index[h].second+1, -1);
            s[j].extract_zeros(i, j);
            h = parent[j];
        }
    }
}

int time_global = 0;
segtree s2;

char buff[22];
char* buff_ptr = buff+19;
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
        if(bugs[i]) {
            death_time[i] = d+1;
        } else {
            death_time[i] = 0;
        }
    }
    for(int i=1; i<=n; i++) {
        fastscan(species[i]);
    }
    for(int i=1; i<=d; i++) {
        fastscan(home[i]);
        query_count[home[i]]++;
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

    dfs3(1);
    pt_t = t_base;
    pt_d = d_base;
    memset(t_base, 0 ,sizeof(t_base));
    memset(d_base, 0, sizeof(d_base));
    s2 = segtree(n);
    for(int i=1; i<=n; i++) {
        if (death_time[i] > 0) {
            s2.inc(preorder_interval[i].first, preorder_interval[i].second, 1);
        }
    }
    sort(die_order.begin(), die_order.end(), [](int a1, int a2){return death_time[a1] < death_time[a2];});
    auto pt = die_order.begin();
    while(pt != die_order.end() && death_time[*pt] == 0) {
        pt++;
    }

    for(int i=1; i<=d; i++) {
        int z = preorder_interval[home[i]].first;
        printf("%d ", s2.point_query(z));
        time_global++;
        while(pt != die_order.end() && death_time[*pt] == i) {
            s2.inc(preorder_interval[*pt].first, preorder_interval[*pt].second, -1);
            pt++;
        }
    }

    printf("\n");
}
