#include <iostream>
#include <cstring>
using namespace std;

const int col[] = {1, 1, 1, 2, 1, 1, 2, 3}; // 1 = available
const int mod = 1e9 + 7;
int N, Q;
char G[3][30010];
int BM[30010]; // 1 = blocked

struct state {
    int64_t ways[1 << 3][1 << 3]; // [s, e). 1 = definitely blocked
    state() { memset(ways, 0, sizeof ways); }
};

struct node {
    int s, e, m;
    state st;
    node *l, *r;
    node(int _s, int _e): s(_s), e(_e) {
        m = s + (e - s) / 2;
        if (s == e) {
            st = init();
            return;
        }
        l = new node(s, m); r = new node(m + 1, e);
        st = combine(l->st, r->st);
    }
    struct state init() {
        struct state ret;
        for (int a = 0; a < (1 << 3); ++a) { // State of first column (not necessarily tiled)
            if ((BM[s] & a) != BM[s]) continue; // Not enough blocked
            for (int b = 0; b < (1 << 3); ++b) { // Horizontal tiles (state of second column)
                if (BM[s] & b) continue; // Blocked
                if ((b & a) != b) continue; // Not subset of blocked tiles
                ret.ways[a][b] += col[a ^ BM[s] ^ b];
            }
        }
        return ret;
    }
    struct state combine(struct state lt, struct state rt) {
        struct state ret;
        for (int a = 0; a < (1 << 3); ++a) { // State of first column
            if ((BM[s] & a) != BM[s]) continue; // Not enough blocked
            for (int b = 0; b < (1 << 3); ++b) { // Banned tiles on e
                for (int c = 0; c < (1 << 3); ++c) { // Protruding
                    (ret.ways[a][b] += lt.ways[a][c] * rt.ways[0b111 ^ c][b]) %= mod;
                }
            }
        }
        return ret;
    }
    void update(int p) {
        if (s == e) return (void)(st = init());
        if (p <= m) l->update(p);
        else r->update(p);
        st = combine(l->st, r->st);
    }
    struct state query(int qs, int qe) {
        if (qs <= s && e <= qe) return st;
        if (qe <= m) return l->query(qs, qe);
        if (qs > m) return r->query(qs, qe);
        return combine(l->query(qs, m), r->query(m + 1, qe));
    }
} *root;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int a = 0; a < 3; ++a)
        for (int b = 1; b <= N; ++b) cin >> G[a][b];
    for (int a = 1; a <= N; ++a) for (int b = 0; b < 3; ++b)
        if (G[b][a] == 'x') BM[a] |= 1 << b;
    root = new node(1, N); // [s, e)
    while (Q--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; cin >> x >> y;
            BM[y] ^= 1 << (--x);
            root->update(y);
        } else {
            int a, b; cin >> a >> b;
            struct state st = root->query(a, b);
            // Can use everything on s, but nothing on e
            cout << st.ways[0b111][0] << '\n';
        }
    }
    return 0;
}