#include <bits/stdc++.h>
using namespace std;

bool f[300000];
long long r[2][300000];
int A[300000][4], vt[300000], p[300000], q[300000], d[300000], id[300000];
vector<pair<pair<int, int>, int> > adj[300000];
vector<pair<long long, pair<int, int> > > w;
priority_queue<pair<pair<long long, int>, pair<int, int> > > pq;

int frt(int i) {return i == id[i] ? i : id[i] = frt(id[i]);}

void pr(int i, int t, int o, int l, long long v) {
    if (vt[i]) return;
    vt[i] = 1;
    if (!t) {p[i] = o; q[i] = l; d[i] = d[o] + !!i;}
    r[t][i] = v;
    for (int j = 0; j < adj[i].size(); ++j) if (!vt[adj[i][j].first.first]) pq.emplace(make_pair(-v - adj[i][j].first.second, adj[i][j].first.first), make_pair(i, adj[i][j].second));
}

void it(int i, int l, long long v) {
    if (vt[i] > -1) {if (l < vt[i]) w.emplace_back(r[0][i] + v, make_pair(l, vt[i] - 1)); return;}
    vt[i] = l;
    for (int j = 0; j < adj[i].size(); ++j) pq.emplace(make_pair(-v - adj[i][j].first.second, adj[i][j].first.first), make_pair(l + f[adj[i][j].second], 0));
}

int main() {
    //freopen("in.txt", "r", stdin);
    int N, M, a, b, x, i, j;
    long long c, t;
    scanf("%d %d", &N, &M);
    for (i = 0; i < M; ++i) {for (j = 0; j < 3; ++j) scanf("%d", &A[i][j]); adj[--A[i][0]].emplace_back(make_pair(--A[i][1], A[i][2]), i); adj[A[i][1]].emplace_back(make_pair(A[i][0], A[i][2]), i);}
    for (i = M - 2; i > -1; --i) A[i][3] = max(A[i + 1][2], A[i + 1][3]);
    pr(0, 0, 0, -1, 0);
    while (!pq.empty()) x = pq.top().first.second, c = -pq.top().first.first, a = pq.top().second.first, b = pq.top().second.second, pq.pop(), pr(x, 0, a, b, c);
    memset(vt, 0, sizeof(vt));
    pr(N - 1, 1, N - 1, -1, 0);
    while (!pq.empty()) x = pq.top().first.second, c = -pq.top().first.first, a = pq.top().second.first, b = pq.top().second.second, pq.pop(), pr(x, 1, a, b, c);
    for (i = 0; i < N; ++i) {id[i] = p[i]; if (i) f[q[i]] = 1;}
    for (i = N - 1; i; i = p[i]) id[i] = i;
    for (i = 0; i < M; ++i) if (!f[i] && (r[0][A[i][0]] + A[i][2] + r[1][A[i][1]] == r[0][N - 1] || r[0][A[i][1]] + A[i][2] + r[1][A[i][0]] == r[0][N - 1])) {
        a = frt(A[i][0]);
        b = frt(A[i][1]);
        if (d[a] > d[b]) swap(a, b);
        while (a != b) id[b] = p[b], b = frt(b);
    }
    memset(f, 0, sizeof(f));
    for (i = frt(N - 1), x = 0; i; i = frt(p[i]), ++x) f[q[i]] = 1, w.emplace_back(r[0][p[i]] + A[q[i]][2] + A[q[i]][3] + r[1][i], make_pair(x, x));
    memset(vt, -1, sizeof(vt));
    it(N - 1, 0, 0);
    while (!pq.empty()) a = pq.top().first.second, b = pq.top().second.first, c = -pq.top().first.first, pq.pop(), it(a, b, c);
    sort(w.begin(), w.end());
    iota(id, id + x + 1, 0);
    t = r[0][N - 1];
    for (i = 0; i < w.size(); ++i) for (j = frt(w[i].second.first); j <= w[i].second.second; j = frt(j)) t = max(t, w[i].first), id[j] = j + 1;
    printf("%lld", t);
    return 0;
}
