#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

vector<tuple<int, int, int> > adj[300001];
int pre[300001], preve[300001], par[300001], depth[300001];
ll dis[2][300001];
void dijkstra(int s, int t) {
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
	dis[t][s] = 0;
	pq.push({0, s});
	ll c; int u;
	while (!pq.empty()) {
		tie(c, u) = pq.top();
		pq.pop();
		if (dis[t][u] != c) continue;
		for (int i=0; i<adj[u].size(); i++) {
			int v, w, b;
			tie(v, w, b) = adj[u][i];
			if (dis[t][v] != -1 && dis[t][v] <= c + w) continue;
			if (t == 0) {
				pre[v] = u;
				preve[v] = b;
				depth[v] = depth[u] + 1;
			}
			dis[t][v] = c + w;
			pq.push({dis[t][v], v});
		}
	}
}
int findp(int u) {
	return u == par[u] ? u : par[u] = findp(par[u]);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	bool isline[300001];
	int n, m, u, v, w, b, warr[300001], inc[300001];
	cin >> n >> m;
	for (int i=1; i<=m; i++) {
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w, i);
		adj[v].emplace_back(u, w, i);
		warr[i] = w;
	}
	inc[m] = 0;
	for (int i=m-1; i; i--) inc[i] = max(inc[i+1], warr[i+1]);
	for (int i=0; i<2; i++) fill(dis[i]+1, dis[i]+n+1, -1);
	dijkstra(1, 0);
	dijkstra(n, 1);
	
	ll lo = dis[0][n] + 1, hi = dis[0][n] + 1e9, ans = dis[0][n], cut;
	bool valid;
	fill(isline+1, isline+m+1, false);
	for (int i=n; i; i=pre[i]) {
		par[i] = i;
		isline[preve[i]] = true;
	}
	while (lo <= hi) {
		cut = (lo + hi) / 2;
		for (int i=1; i<=n; i++) par[i] = pre[i];
		for (int i=n; i; i=pre[i]) par[i] = i;
		for (int i=1; i<=n; i++) {
			for (auto tup : adj[i]) {
				tie(v, w, b) = tup;
				u = i;
				if (min(dis[0][u]+dis[1][v], dis[0][v]+dis[1][u]) + w >= cut) continue;
				if (isline[b]) continue;
				u = findp(u), v = findp(v);
				if (depth[u] > depth[v]) swap(u, v);
				while (v != u) {
					par[v] = pre[v];
					v = findp(v);
				}
			}
		}
		v = findp(n);
		valid = false;
		while (v > 1) {
			u = pre[v], b = preve[v], w = warr[preve[v]];
			if (min(dis[0][u]+dis[1][v], dis[0][v]+dis[1][u]) + w + inc[b] >= cut) valid = true;
			v = findp(pre[v]);
		}
		if (valid) {
			ans = cut;
			lo = cut + 1;
		}
		else hi = cut - 1;
	}
	cout << ans;
}
