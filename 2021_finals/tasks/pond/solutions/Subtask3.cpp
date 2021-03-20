#include <bits/stdc++.h>
using namespace std;

long long A[300000], s[300000], r[2][300000][2];

int main() {
    //freopen("in.txt", "r", stdin);
    long long N, K, t = LLONG_MAX, i, j;
    scanf("%lld %lld", &N, &K);
    --K;
    memset(r, -1, sizeof(r));
    r[0][K][0] = 0;
    for (i = 0; i < N - 1; ++i) scanf("%lld", &A[i]), s[i + 1] += s[i] + A[i];
    for (j = 0; j < N - 1; ++j) {
        for (i = max(K - j, 0LL); i + j < min(j + K + 1, N); ++i) {
            if (r[j % 2][i + j][1] > -1) if (r[j % 2][i + j][0] < 0 || r[j % 2][i + j][0] > r[j % 2][i + j][1] + (s[i + j] - s[i]) * (N - i - j - 1)) r[j % 2][i + j][0] = r[j % 2][i + j][1] + (s[i + j] - s[i]) * (N - i - j - 1);
            if (r[j % 2][i + j][0] > -1) if (r[j % 2][i + j][1] < 0 || r[j % 2][i + j][1] > r[j % 2][i + j][0] + (s[i + j] - s[i]) * i) r[j % 2][i + j][1] = r[j % 2][i + j][0] + (s[i + j] - s[i]) * i;
            if (i) if (r[(j + 1) % 2][i + j][0] < 0 || r[(j + 1) % 2][i + j][0] > r[j % 2][i + j][0] + A[i - 1] * (N - i - j - 1)) r[(j + 1) % 2][i + j][0] = r[j % 2][i + j][0] + A[i - 1] * (N - i - j - 1);
            if (i + j < N - 1) if (r[(j + 1) % 2][i + j + 1][1] < 0 || r[(j + 1) % 2][i + j + 1][1] > r[j % 2][i + j][1] + A[i + j] * i) r[(j + 1) % 2][i + j + 1][1] = r[j % 2][i + j][1] + A[i + j] * i;
        }
        //printf("%lld %lld\n", r[j % 2][K][0], r[j % 2][K][1]);
        for (i = max(K - j, 0LL); i + j < min(j + K + 1, N); ++i) r[j % 2][i + j][0] = r[j % 2][i + j][1] = -1;
    }
    t = min(r[(N - 1) % 2][N - 1][0] > -1 ? r[(N - 1) % 2][N - 1][0] : 1000000000000000000, r[(N - 1) % 2][N - 1][1] > -1 ? r[(N - 1) % 2][N - 1][1] : 1000000000000000000) * 2;
    for (i = 0; i < N; ++i) t += abs(s[K] - s[i]);
    printf("%lld", t);
    return 0;
}
