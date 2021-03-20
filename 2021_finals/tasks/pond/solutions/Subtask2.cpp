#include <bits/stdc++.h>
using namespace std;

long long A[300000], s[300000], r[2][2000][2], z[300000];

int main() {
    //freopen("in.txt", "r", stdin);
    long long N, K, t = LLONG_MAX, i, j;
    scanf("%lld %lld", &N, &K);
    --K;
    memset(r, -1, sizeof(r));
    r[0][K][0] = 0;
    for (i = 0; i < N - 1; ++i) scanf("%lld", &A[i]), s[i + 1] += s[i] + A[i];
    for (j = 0; j < N; ++j) {
        //if (!(j % 1000)) fprintf(stderr, "%d\n", j);
        for (i = 0; i + j < N; ++i) if (r[0][i + j][0] > -1 || r[0][i + j][1] > -1) {
            if (r[0][i + j][1] > -1) if (r[0][i + j][0] < 0 || r[0][i + j][0] > r[0][i + j][1] + (s[i + j] - s[i]) * (N - i - j - 1)) r[0][i + j][0] = r[0][i + j][1] + (s[i + j] - s[i]) * (N - i - j - 1);
            if (r[0][i + j][0] > -1) if (r[0][i + j][1] < 0 || r[0][i + j][1] > r[0][i + j][0] + (s[i + j] - s[i]) * i) r[0][i + j][1] = r[0][i + j][0] + (s[i + j] - s[i]) * i;
            if (i) if (r[1][i + j][0] < 0 || r[1][i + j][0] > r[0][i + j][0] + A[i - 1] * (N - i - j - 1)) r[1][i + j][0] = r[0][i + j][0] + A[i - 1] * (N - i - j - 1);
            if (i + j < N - 1) if (r[1][i + j + 1][1] < 0 || r[1][i + j + 1][1] > r[0][i + j][1] + A[i + j] * i) r[1][i + j + 1][1] = r[0][i + j][1] + A[i + j] * i;
            if (!i) z[i + j] = r[0][i + j][0];
        }
        swap(r[0], r[1]);
        memset(r[1], -1, sizeof(r[1]));
    }
    //for (i = 0; i < K + 1; ++i) for (j = K; j < N; ++j) printf("(%lld %lld)%c", r[i][j][0] * 2, r[i][j][1] * 2, j < N - 1 ? ' ' : '\n');
    for (i = K; i < N; ++i) t = min(t, max(z[i] * 2, 0LL));
    for (i = 0; i < N; ++i) t += abs(s[K] - s[i]);
    printf("%lld", t);
    return 0;
}
