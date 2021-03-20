#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

using pi = pair<int, int>;
int N, K;
int A[300010], P[300010], D[300010], C[300010];
vector<pi> V;

struct node {
    int S, E, M;
    int64_t SUM, M_PSUM;
    node *L, *R;
    node(int _S, int _E): S(_S), E(_E) {
        M = S + (E - S) / 2;
        if (S == E) {
            SUM = M_PSUM = C[S];
            return;
        }
        L = new node(S, M); R = new node(M + 1, E);
        SUM = L->SUM + R->SUM;
        M_PSUM = min(L->M_PSUM, L->SUM + R->M_PSUM);
    }
    void up(int QP, int QV) {
        if (S == E) {
            SUM += QV;
            M_PSUM += QV;
            return;
        }
        if (QP <= M) L->up(QP, QV);
        else R->up(QP, QV);
        SUM = L->SUM + R->SUM;
        M_PSUM = min(L->M_PSUM, L->SUM + R->M_PSUM);
    }
} *root;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    ++K;
    // Reduce to single array problem
    for (int a = 1; a <= N; ++a) {
        cin >> A[a]; // 0 <= A < K
        assert(0 <= A[a] && A[a] < K);
    }
    for (int a = 1; a <= N; ++a) {
        cin >> P[a]; // 0 <= P < K
        assert(0 <= P[a] && P[a] < K);
        A[a] -= P[a]; // A = P (mod K) <=> P - A = 0 (mod K)
        // -K < A < K
        assert(-K < A[a] && A[a] < K);
        if (A[a] < 0) A[a] += K; // 0 <= A < K
        assert(0 <= A[a] && A[a] < K);
    }
    // Now we want to make A[i] = 0 (mod K) for 1 <= i <= N

    // Reduce to point updates
    for (int a = 1; a <= N + 1; ++a) {
        D[a] = A[a] - A[a - 1]; // -K < D < K
        assert(-K < D[a] && D[a] < K);
        if (D[a] < 0) D[a] += K; // 0 <= D < K
        assert(0 <= D[a] && D[a] < K);
    }
    // Equivalently, D[i] = 0 (mod K) for 1 <= i <= N + 1
    // Each operation [i, j] +1 to D[i] and -1 to D[j + 1]

    // Let C[i] represent the net change to position i
    // Initially let C[i] = K - D[i] (i.e. increase)
    int64_t S = 0;
    for (int a = 1; a <= N + 1; ++a) {
        C[a] = K - D[a]; // 1 <= C[a] <= K
        assert(1 <= C[a] && C[a] <= K);
        S += C[a];
    }
    assert(S % K == 0);
    S /= K;

    root = new node(1, N + 1);
    // Hence sum(C[i]) = (N + 1)K - (D[1] + ... + D[N + 1])
    // Note that D[1] + ... + D[N + 1] = 0 (mod K) so sum(C[i]) = SK for some S
    // Eventually we need sum(C[i]) = 0 (since +1s come with -1s)
    for (int a = 1; a <= N + 1; ++a) V.emplace_back(D[a], -a);
    sort(V.begin(), V.end());
    // Changing K - D[i] to -D[i] subtracts K so we do this S times
    // Total change = |-D[i]| - |K - D[i]| = 2 * D[i] - K so better to change small D[i]
    // Better to change larger position in case of ties by exchange argument
    for (auto [val, pos]: V) {
        root->up(-pos, -K);
        if (root->M_PSUM >= 0) { // Min prefix
            C[-pos] -= K;
            --S;
        } else {
            root->up(-pos, K);
        }
        if (!S) break;
    }
    assert(S == 0);

    int64_t ans = 0;
    for (int a = 1; a <= N + 1; ++a) ans += abs(C[a]);
    assert(ans % 2 == 0);
    ans /= 2;
    cout << ans << '\n';
    return 0;
}