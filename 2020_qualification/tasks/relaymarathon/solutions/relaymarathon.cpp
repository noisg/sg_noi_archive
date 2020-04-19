#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

vector<pair<int, int> > adj[N];
int n, d[N], dx1[N], dy1[N], p[N];
set<int> S;
bool vis[N];
bool skip[N];
vector<pair<pair<int, int>, int> > E;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;

void djikstra() {
  while(!Q.empty()) {
    int u = Q.top().second;
    Q.pop();
    if(vis[u]) continue;
    vis[u] = 1;
    for(auto nbr : adj[u]) {
      int v = nbr.first, w = nbr.second;
      if(skip[v]) continue;
      if(d[u] + w < d[v]) {
        d[v] = d[u] + w;
        Q.push({d[v], v});
        p[v] = p[u];
      }
    }
  }
}

void run(int src) {
  while(!Q.empty()) Q.pop();
  for(int i = 1; i <= n + 4; i++) d[i] = INT_MAX, vis[i] = 0;
  d[src] = 0;
  p[src] = src;
  Q.push({0, src});
  djikstra();
}

pair<pair<int, int>, int> run_nearest() {
  while(!Q.empty()) Q.pop();
  for(int i = 1; i <= n + 4; i++) d[i] = INT_MAX, vis[i] = 0;
  for(auto u : S) {
    if(skip[u]) continue;
    Q.push({0, u});
    d[u] = 0;
    p[u] = u;
  }
  djikstra();
  int ans = INT_MAX, a = -1, b = -1;
  for(auto e : E) {
    int u = e.first.first, v = e.first.second, w = e.second;
    if(skip[u] == 1 or skip[v] == 1)  continue;
    if(d[u] == INT_MAX or d[v] == INT_MAX or p[u] == p[v])  continue;
    if(ans > d[u] + w + d[v]) {
      ans = d[u] + w + d[v];
      a = p[u], b = p[v];
    }
  }
  return {{a, b}, ans};
}

int main() {
  cin.tie(NULL);
  ios::sync_with_stdio(false);
  srand(time(NULL));
  int m, k, u, v, w;
  cin>>n>>m>>k;
  while(m--) {
    cin>>u>>v>>w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
    E.push_back({{u, v}, w});
  }

  for(int i = 1; i <= k; i++) {
    cin>>u;
    S.insert(u);
  }

  pair<pair<int, int>, int> tmp = run_nearest();

  int x1 = tmp.first.first, y1 = tmp.first.second, d1 = tmp.second;
  int c1 = -1, c2 = -1;

  run(x1);
  for(int i = 1; i <= n; i++) dx1[i] = d[i];
  run(y1);
  for(int i = 1; i <= n; i++) dy1[i] = d[i];

  for(auto c : S) {
    if(c == x1 or c == y1)  continue;
    if(c1 == -1 or dy1[c] <= dy1[c1]) {
      c2 = c1;
      c1 = c;
    } else if(c2 == -1 or dy1[c] < dy1[c2]) {
      c2 = c;
    }
  }

  int ans = INT_MAX, a1 = -1, a2 = -1, a3 = -1, a4 = -1;
  if(dx1[c1] != INT_MAX and dy1[c2] != INT_MAX) {
    if(ans > dx1[c1] + dy1[c2]) {
      ans = dx1[c1] + dy1[c2];
      a1 = x1, a2 = c1, a3 = y1, a4 = c2;
    }
  }
  for(auto x2 : S) {
    if(x2 == x1 or x2 == y1 or x2 == c1)  continue;
    if(dx1[x2] != INT_MAX and dy1[c1] != INT_MAX) {
      if(ans > dx1[x2] + dy1[c1]) {
        ans = dx1[x2] + dy1[c1];
        a1 = x1, a2 = x2, a3 = y1, a4 = c1;
      }
    }
  }

  //Try commenting this portion and then checking if it fails or not.
  skip[x1] = skip[y1] = 1;
  tmp = run_nearest();
  int d2 = tmp.second;
  if(d1 != INT_MAX and d2 != INT_MAX) {
    if(ans > d1 + d2) {
      ans = d1 + d2;
      a1 = x1, a2 = y1, a3 = tmp.first.first, a4 = tmp.first.second;
    }
  }

  cout<<ans<<endl;
  //cerr<<a1<<" "<<a2<<" "<<a3<<" "<<a4<<endl;
}
