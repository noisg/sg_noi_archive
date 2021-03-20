#include <bits/stdc++.h>
using namespace std;

long long N, A[2000];
bool vt[2000][2000][2];
priority_queue<pair<long long, pair<pair<long long, long long>, long long> > > pq;

void it(long long i, long long j, long long s, long long v) {
    if (vt[i][j][s]) return;
    vt[i][j][s] = 1;
    if (!s) {
        if (i) pq.emplace(-v - (A[i] - A[i - 1]) * (N - j + i - 1), make_pair(make_pair(i - 1, j), 0));
        if (j < N - 1) pq.emplace(-v - (A[j + 1] - A[i]) * (N - j + i - 1), make_pair(make_pair(i, j + 1), 1));
    } else {
        if (i) pq.emplace(-v - (A[j] - A[i - 1]) * (N - j + i - 1), make_pair(make_pair(i - 1, j), 0));
        if (j < N - 1) pq.emplace(-v - (A[j + 1] - A[j]) * (N - j + i - 1), make_pair(make_pair(i, j + 1), 1));
    }
}

int main() {
    long long K, i, j;
    scanf("%lld %lld", &N, &K);
    for (i = 1; i < N; ++i) scanf("%lld", &A[i]), A[i] += A[i - 1];
    it(K - 1, K - 1, 0, 0);
    while (pq.top().second.first.first || pq.top().second.first.second < N - 1) it(pq.top().second.first.first, pq.top().second.first.second, pq.top().second.second, -pq.top().first), pq.pop();
    printf("%lld", -pq.top().first);
    return 0;
}
