#include <bits/stdc++.h>
using namespace std;

long long A[3000], s[3000], r[3000][3000][2];
vector<long long> v;
stack<long long> st;

int main() {
    freopen("in.txt", "r", stdin);
    long long N, K, vN, vK, l, t = LLONG_MAX, i, j;
    scanf("%lld %lld", &N, &K);
    --K;
    memset(r, -1, sizeof(r));
    for (i = 0; i < N - 1; ++i) scanf("%lld", &A[i]), s[i + 1] += s[i] + A[i];
    //for (i = 0; i < N - 1; ++i) printf("%lld %lld: %lld\n", i, i + 1, A[i]);
    for (i = K - 1; i > 0; --i) if (A[i - 1] > A[i]) st.push(i);
    st.push(0);
    vK = st.size() - !K;
    r[vK][vK][0] = 0;
    while (!st.empty()) v.push_back(st.top()), st.pop();
    if (K) v.push_back(K);
    for (i = K + 1; i < N - 1; ++i) if (A[i] > A[i - 1]) v.push_back(i);
    v.push_back(N - 1);
    printf("%lld %lld\n", vN, vK);
    for (i = 0; i < v.size(); ++i) printf("%lld%c", v[i], i < v.size() - 1 ? ' ' : '\n');
    vN = v.size();
    for (j = 0; j < vN - 1; ++j) for (i = 0; i + j < vN; ++i) if (r[i][i + j][0] > -1 || r[i][i + j][1] > -1) {
        if (r[i][i + j][1] > -1) if (r[i][i + j][0] < 0 || r[i][i + j][0] > r[i][i + j][1] + (s[v[i + j]] - s[v[i]]) * (N - v[i + j] - 1)) r[i][i + j][0] = r[i][i + j][1] + (s[v[i + j]] - s[v[i]]) * (N - v[i + j] - 1);
        if (r[i][i + j][0] > -1) if (r[i][i + j][1] < 0 || r[i][i + j][1] > r[i][i + j][0] + (s[v[i + j]] - s[v[i]]) * v[i]) r[i][i + j][1] = r[i][i + j][0] + (s[v[i + j]] - s[v[i]]) * v[i];
        if (i) if (r[i - 1][i + j][0] < 0 || r[i - 1][i + j][0] > r[i][i + j][0] + (s[v[i]] - s[v[i - 1]]) * (N - v[i + j] - 1)) r[i - 1][i + j][0] = r[i][i + j][0] + (s[v[i]] - s[v[i - 1]]) * (N - v[i + j] - 1);
        if (i + j < vN - 1) if (r[i][i + j + 1][1] < 0 || r[i][i + j + 1][1] > r[i][i + j][1] + (s[v[i + j + 1]] - s[v[i + j]]) * v[i]) r[i][i + j + 1][1] = r[i][i + j][1] + (s[v[i + j + 1]] - s[v[i + j]]) * v[i];
    }
    for (i = 0; i < vK + 1; ++i) for (j = vK; j < vN; ++j) printf("(%lld %lld)%c", r[i][j][0] * 2, r[i][j][1] * 2, j < vN - 1 ? ' ' : '\n');
    for (i = vK; i < vN; ++i) t = min(t, max(r[0][i][0] * 2, 0LL));
    for (i = 0; i < N; ++i) t += abs(s[K] - s[i]);
    printf("%lld", t);
    return 0;
}
