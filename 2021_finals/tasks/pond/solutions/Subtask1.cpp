#include <bits/stdc++.h>
using namespace std;

bool vt[100][100][100];
long long N, K, A[300000];
priority_queue<pair<long long, pair<pair<long long, long long>, long long> > > pq;

void it(long long i, long long j, long long p, long long v) {
    if (vt[i][j][p]) return;
    else vt[i][j][p] = 1;
    if (i) pq.emplace(-v - A[p - 1] * (N - j + i - 1), make_pair(make_pair(min(i, p - 1), j), p - 1));
    if (j < N - 1) pq.emplace(-v - A[p] * (N - j + i - 1), make_pair(make_pair(i, max(j, p + 1)), p + 1));
}

int main() {
    //freopen("in.txt", "r", stdin);
    long long a, b, c, v, i;
    scanf("%lld %lld", &N, &K);
    --K;
    for (i = 0; i < N - 1; ++i) scanf("%lld", &A[i]);
    it(K, K, K, 0);
    while (pq.top().second.first.first || pq.top().second.first.second < N - 1) {
        v = -pq.top().first;
        a = pq.top().second.first.first;
        b = pq.top().second.first.second;
        c = pq.top().second.second;
        pq.pop();
        it(a, b, c, v);
    }
    printf("%lld", -pq.top().first);
    return 0;
}
