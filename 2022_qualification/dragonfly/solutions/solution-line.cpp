#include <bits/stdc++.h>
using namespace std;
// line
const int n_max = 2e5+10;
int bugs[n_max];
int species[n_max];
int home[n_max];
int t[n_max * 8];
int d[n_max * 8];
int death_time[n_max];
struct segtree {
    int n;
    int n0;
    int n_bits;
    segtree(int _n) {
        n0 = _n;
        n_bits = 32 - __builtin_clz(_n + 1);
        n = (1<<n_bits);
        t[n] = 2e9;
        for(int i=n-1; i>=1; i--) {
            t[i] = min(t[i*2], t[i*2+1]);
        }
    }
    void reset() {
        for(int i=2*n; i>=1; i--) {
            t[i] = 0;
            d[i] = 0;
        }
    }
    int point_query(int x) {
        x += n;
        int ans = t[x];
        while(x) {
            ans += d[x];
            x /= 2;
        }
        return ans;
    }
    segtree() {}
    void apply(int p, int value) {
        assert(t);
        t[p] += value;
        if (p < n) d[p] += value;
    }

    void inc(int l, int r, int value) { // includes l, excludes r
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

    void build(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
        }
    }

    void point_update(int l, int value) {
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

    int find_zero() {
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
    /*int query(int l, int r) { // includes l, excludes r
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

    void extract_zeros(int i) {
        while(true) {
            int k = find_zero();
            if(k>=n0) break;
            death_time[k] = i;
            point_update(k, 2e9);
        }
    }
};

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

segtree seg(n_max);

int next_child[n_max]; // given a node, the "next child" is the node activated once it dies
int last_of_species[n_max];
bitset<n_max> species_root;

bool is_active[n_max];

int time_global = 0;
void activate(int x) {

    if(x==0) return;
    assert(!is_active[x]);
    if(death_time[x] > time_global) { // then we should activate it
        seg.inc(x, n_max-1, 1);
        is_active[x] = true;
    } else {
        activate(next_child[x]);
    }
}

void deactivate(int x) {
    if(x==0) return;

    if(!is_active[x]) {
        return;
    }
    seg.inc(x, n_max-1, -1);
    activate(next_child[x]);
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
    }
    for(int i=1; i<n; i++) {
        // discard the graph since we already know it
        int u,v;
        fastscan(u);
        fastscan(v);
    }
    species_root.set();

    for(int i=1; i<=n; i++) {
        if(last_of_species[species[i]]) {
            assert(species[last_of_species[species[i]]] == species[i]);
            next_child[last_of_species[species[i]]] = i;
            species_root[i] = false;

        }
        last_of_species[species[i]] = i;

    }
    for(int i=1; i<=n; i++) {
        seg.point_update(i, bugs[i]);
    }
    for(int i=1; i<=d; i++) {
        seg.inc(0, home[i]+1, -1);
        int z;
        while((z = seg.find_zero()) < n+1) {
            seg.point_update(z, 2e9);
            death_time[z] = i;

        }
    }
    seg.reset();
    for(int i=1; i<=n; i++) {
        if(species_root[i] && death_time[i]>0) {
            activate(i);
            is_active[i] = true;
        }
    }
    vector<int> die_order(n);
    for(int i=1; i<=n; i++) {
        die_order[i-1] = i;
    }
    sort(die_order.begin(), die_order.end(),
         [](int a1, int a2){return death_time[a1] < death_time[a2];});
    auto pt = die_order.begin();
    while(pt != die_order.end() && death_time[*pt]==0) {
        pt++;
    }
    for(int i=1; i<=d; i++) {
        int z = home[i];
        printf("%d ", seg.point_query(z));
        time_global++;
        while(pt != die_order.end() && death_time[*pt] == i) {
            deactivate(*pt);
            is_active[*pt] = false;
            pt++;
        }
    }
    printf("\n");
}
