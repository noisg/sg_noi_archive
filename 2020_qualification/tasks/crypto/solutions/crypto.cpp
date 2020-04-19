#include <iostream>
#include <algorithm>
using namespace std;

const long long MOD = 1e9 + 7;
long long F[300010] = {1};
long long ANS = 1;
int N;
int P[300010], P2[300010];

int FT[300010];
void update(int X, int V) {
    for (; X <= N; X += X & -X)
        FT[X] += V;
}
int query(int X) {
    int RET = 0;
    for (; X; X -= X & -X)
        RET += FT[X];
    return RET;
}
void solve() {
    for (int a = 1; a <= N; ++a) {
        FT[a] += 1;
        int b = a + (a & -a);
        if (b <= N) FT[b] += FT[a];
    }
    for (int a = 1; a <= N; ++a) {
        (ANS += (query(P[a]) - 1) * F[N - a]) %= MOD;
        update(P[a], -1);
    }
    cout << ANS << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int a = 1; a <= N; ++a) {
        cin >> P[a];
        P2[a] = P[a];
    }
    sort(P2 + 1, P2 + N + 1);
    for (int a = 1; a <= N; ++a)
        P[a] = lower_bound(P2 + 1, P2 + N + 1, P[a]) - P2;
    for (int a = 1; a < N; ++a)
        (F[a] = F[a - 1] * a) %= MOD;
    solve();
    return 0;
}
