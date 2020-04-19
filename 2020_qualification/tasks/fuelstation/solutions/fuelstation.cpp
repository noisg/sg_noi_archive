#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

typedef pair<int, int> pi;
int N, D;
struct station {
    int X, A, B;
    station() {}
    station(int _X, int _A, int _B): X(_X), A(_A), B(_B) {}
    bool operator <(const station &o) const {
        return tie(X, A, B) < tie(o.X, o.A, o.B);
    }
} STN[300010];

struct node {
    int S, E, M;
    int64_t LAZY, V; // Min val
    node *L, *R;
    node(int _S, int _E): S(_S), E(_E), M((_S + _E) / 2) {
        V = LAZY = 0;
        if (S == E) return;
        L = new node(S, M); R = new node(M + 1, E);
    }
    int64_t val() {
        return V + LAZY;
    }
    void push() {
        if (LAZY) {
            L->LAZY += LAZY;
            R->LAZY += LAZY;
            V += LAZY;
            LAZY = 0;
        }
    }
    void update(int QS, int QE, int QV) { // Range Update Add
        if (QS <= S && E <= QE) return (void)(LAZY += QV);
        push();
        if (QE <= M) L->update(QS, QE, QV);
        else if (QS > M) R->update(QS, QE, QV);
        else { L->update(QS, M, QV); R->update(M + 1, QE, QV); }
        V = min(L->val(), R->val());
    }
} *root;

vector<pi> V;
int NXT[300010];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> D;
    root = new node(1, N + 1);
    for (int a = 1; a <= N; ++a) cin >> STN[a].X >> STN[a].A >> STN[a].B;
    sort(STN + 1, STN + N + 1);
    int XPTR = 1;
    STN[N + 1] = station(D, 0, D);
    for (int a = 1; a <= N + 1; ++a) if (STN[a].X != STN[XPTR].X)
        for (; XPTR < a; ++XPTR) NXT[XPTR] = a;
    NXT[N + 1] = N + 1;
    for (int a = 1; a <= N + 1; ++a) V.emplace_back(STN[a].B, a);
    sort(V.begin(), V.end()); // Sort by B
    for (int a = 0; a <= N; ++a) root->update(V[a].second, V[a].second, -STN[V[a].second].X); // -X to this location
    for (int a = 0; a <= N; ++a)
        root->update(NXT[V[a].second], N + 1, STN[V[a].second].A); // +A to locations after
    int F = 0, BPTR = 0;
    for (int a = 0; a <= N; ++a) {
        root->update(1, N + 1, V[a].first - F); // Increase in fuel
        if (a && V[a].first != F)
            for (; BPTR < a; ++BPTR)
                root->update(NXT[V[BPTR].second], N + 1, -STN[V[BPTR].second].A); // Remove station
        F = V[a].first;
        int64_t mval = root->val();
        if (mval >= 0) {
            cout << F - mval << '\n';
            return 0;
        }
    }
    return 0;
}
