#include <bits/stdc++.h>
using namespace std;

long long A[300000], s[300000], r[2][300000][2];
vector<long long> v;
stack<long long> st;

inline long long sc() {
    long long i;
    char c;
    while ((c = getchar()) < '0' || '9' < c);
    i = c - '0';
    while ('0' <= (c = getchar()) && c <= '9') i *= 10, i += c - '0';
    return i;
}

int main() {
    //freopen("in.txt", "r", stdin);
    long long N = sc(), K = sc(), vN, vK, l, t = LLONG_MAX, i, j;
    --K;
    memset(r, -1, sizeof(r));
    for (i = 0; i < N - 1; ++i) s[i + 1] += s[i] + (A[i] = sc());
    //for (i = 0; i < N - 1; ++i) if ((i + 1) % 100) assert(A[i] >= A[i + 1]);
    //for (i = 0; i < N - 1; ++i) printf("%lld %lld: %lld\n", i, i + 1, A[i]);
    for (i = K - 1; i > 0; --i) if (A[i - 1] > A[i]) st.push(i);
    st.push(0);
    vK = st.size() - !K;
    r[0][vK][0] = 0;
    while (!st.empty()) v.push_back(st.top()), st.pop();
    if (K) v.push_back(K);
    for (i = K + 1; i < N - 1; ++i) if (A[i] > A[i - 1]) v.push_back(i);
    v.push_back(N - 1);
    //for (i = 0; i < v.size(); ++i) printf("%lld%c", v[i], i < v.size() - 1 ? ' ' : '\n');
    vN = v.size();
    for (j = 0; j < vN - 1; ++j) {
        for (i = max(vK - j, 0LL); i + j < min(j + vK + 1, vN); ++i) {
            if (r[j % 2][i + j][1] > -1) if (r[j % 2][i + j][0] < 0 || r[j % 2][i + j][0] > r[j % 2][i + j][1] + (s[v[i + j]] - s[v[i]]) * (N - v[i + j] - 1)) r[j % 2][i + j][0] = r[j % 2][i + j][1] + (s[v[i + j]] - s[v[i]]) * (N - v[i + j] - 1);
            if (r[j % 2][i + j][0] > -1) if (r[j % 2][i + j][1] < 0 || r[j % 2][i + j][1] > r[j % 2][i + j][0] + (s[v[i + j]] - s[v[i]]) * v[i]) r[j % 2][i + j][1] = r[j % 2][i + j][0] + (s[v[i + j]] - s[v[i]]) * v[i];
            if (i) if (r[(j + 1) % 2][i + j][0] < 0 || r[(j + 1) % 2][i + j][0] > r[j % 2][i + j][0] + (s[v[i]] - s[v[i - 1]]) * (N - v[i + j] - 1)) r[(j + 1) % 2][i + j][0] = r[j % 2][i + j][0] + (s[v[i]] - s[v[i - 1]]) * (N - v[i + j] - 1);
            if (i + j < vN - 1) if (r[(j + 1) % 2][i + j + 1][1] < 0 || r[(j + 1) % 2][i + j + 1][1] > r[j % 2][i + j][1] + (s[v[i + j + 1]] - s[v[i + j]]) * v[i]) r[(j + 1) % 2][i + j + 1][1] = r[j % 2][i + j][1] + (s[v[i + j + 1]] - s[v[i + j]]) * v[i];
        }
        //printf("%lld %lld\n", r[j % 2][vK][0], r[j % 2][vK][1]);
        for (i = max(vK - j, 0LL); i + j < min(j + vK + 1, vN); ++i) r[j % 2][i + j][0] = r[j % 2][i + j][1] = -1;
    }
    t = min(r[(vN - 1) % 2][vN - 1][0] > -1 ? r[(vN - 1) % 2][vN - 1][0] : 1000000000000000000, r[(vN - 1) % 2][vN - 1][1] > -1 ? r[(vN - 1) % 2][vN - 1][1] : 1000000000000000000) * 2;
    for (i = 0; i < N; ++i) t += abs(s[K] - s[i]);
    printf("%lld", t);
    return 0;
}
