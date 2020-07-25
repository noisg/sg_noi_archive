#include <bits/stdc++.h>
using namespace std;

long long r[2][300000];
bool vt[300000], f[300000];
int A[300000][4], p[300000], q[300000], d[300000], id[300000];
vector<pair<pair<int, int>, int> > adj[300000];
priority_queue<pair<pair<long long, int>, pair<int, int> > > pq;

int frt(int i) {return i == id[i] ? i : id[i] = frt(id[i]);}

void it(int i, int t, int o, int l, long long v) {
    if (vt[i]) return;
    vt[i] = 1;
    if (!t) {p[i] = o; q[i] = l; d[i] = d[o] + !!i;}
    r[t][i] = v;
    for (int j = 0; j < adj[i].size(); ++j) if (!vt[adj[i][j].first.first]) pq.emplace(make_pair(-v - adj[i][j].first.second, adj[i][j].first.first), make_pair(i, adj[i][j].second));
}

int main() {
    //freopen("in.txt", "r", stdin);
    int N, M, a, b, x, i, j;
    long long l, h, c;
    bool e;
    scanf("%d %d", &N, &M);
    for (i = 0; i < M; ++i) {for (j = 0; j < 3; ++j) scanf("%d", &A[i][j]); adj[--A[i][0]].emplace_back(make_pair(--A[i][1], A[i][2]), i); adj[A[i][1]].emplace_back(make_pair(A[i][0], A[i][2]), i);}
    for (i = M - 2; i > -1; --i) A[i][3] = max(A[i + 1][2], A[i + 1][3]);
    it(0, 0, 0, -1, 0);
    while (!pq.empty()) x = pq.top().first.second, c = -pq.top().first.first, a = pq.top().second.first, b = pq.top().second.second, pq.pop(), it(x, 0, a, b, c);
    memset(vt, 0, sizeof(vt));
    it(N - 1, 1, N - 1, -1, 0);
    while (!pq.empty()) x = pq.top().first.second, c = -pq.top().first.first, a = pq.top().second.first, b = pq.top().second.second, pq.pop(), it(x, 1, a, b, c);
    h = (l = r[0][N - 1]) + 1000000000;
    //for (i = 0; i < M; ++i) printf("%d: %d %d %d %d\n", i, A[i][0], A[i][1], A[i][2], A[i][3]);
    while (l < h) {
        e = 0;
        c = (l + h + 1) / 2;
        //printf("%lld %lld %lld:\n", l, h, c);
        for (i = 0; i < N; ++i) {id[i] = p[i]; if (i) f[q[i]] = 1;}
        for (i = N - 1; i; i = p[i]) id[i] = i;
        for (i = 0; i < M; ++i) if (!f[i] && (r[0][A[i][0]] + A[i][2] + r[1][A[i][1]] < c || r[0][A[i][1]] + A[i][2] + r[1][A[i][0]] < c)) {
            a = frt(A[i][0]);
            b = frt(A[i][1]);
            if (d[a] > d[b]) swap(a, b);
            //printf("%d %d | %d %d\n", a, b, d[a], d[b]);
            while (a != b) id[b] = p[b], b = frt(b);
        }
        for (i = frt(N - 1); i && !e; i = frt(p[i])) e = (c <= r[0][A[q[i]][0]] + A[q[i]][2] + A[q[i]][3] + r[1][A[q[i]][1]] && c <= r[0][A[q[i]][1]] + A[q[i]][2] + A[q[i]][3] + r[1][A[q[i]][0]]);
        //for (i = frt(N - 1); i; i = frt(p[i])) printf("! %d _ %d %d %d (%d)\n", q[i], A[q[i]][0], A[q[i]][1], A[q[i]][2], A[q[i]][3]);
        (e ? l : h) = c - !e;
        //printf("\n");
    }
    printf("%lld", (l + h) / 2);
    return 0;
}
