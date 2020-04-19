#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
vector<pair<ll, ll> > vec;
struct node {
	ll s, e, m;
	ll mn, lz;
	node *l, *r;
	node(ll _s, ll _e): s(_s), e(_e), m((_s+_e)/2), lz(0) {
		if (s == e) {
			mn = -vec[s].first;
			return;
		}
		l = new node(s, m);
		r = new node(m+1, e);
		mn = min(l->mn, r->mn);
	}
	void prop() {
		l->update(s, m, lz);
		r->update(m+1, e, lz);
		lz = 0;
		mn = min(l->mn, r->mn);
	}
	void update(ll x, ll y, ll v) {
		if (x > y) return;
		if (x <= s && y >= e) {
			mn += v;
			lz += v;
			return;
		}
		if (lz != 0) prop();
		if (x <= m) l->update(x, y, v);
		if (y >= m+1) r->update(x, y, v);
		mn = min(l->mn, r->mn);
	}
};
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n, d, x, a, b, ans;
	vector<tuple<ll, ll, ll> > vec2;
	cin >> n >> d;
	ans = d;
	for (ll i=0; i<n; i++) {
		cin >> x >> a >> b;
		vec.emplace_back(x, i);
		vec2.emplace_back(b, a, x);
	}
	vec.emplace_back(d, n);
	vec2.emplace_back(2000000000, 0, d);
	sort(vec.begin(), vec.end());
	ll cnt = n+1;
	for (ll i=n; i>=0; i--) {
		if (i != n && vec[i].first != vec[i+1].first) cnt = i + 1;
		get<2>(vec2[vec[i].second]) = cnt;
	}
	sort(vec2.begin(), vec2.end());
	node *root = new node(0, n);
	for (ll i=0; i<n; i++) {
		root->update(get<2>(vec2[i]), n, get<1>(vec2[i]));		
	}
	ll left = 0;
	for (ll i=0; i<=n; i++) {
		root->update(0, n, get<0>(vec2[i]) - (i == 0 ? 0 : get<0>(vec2[i-1])));
		if (i < n-1 && get<0>(vec2[i]) == get<0>(vec2[i+1])) continue;
		while (get<0>(vec2[left]) != get<0>(vec2[i])) {
			root->update(get<2>(vec2[left]), n, -get<1>(vec2[left]));
			left++;
		}
		if (root->mn < 0) continue;
		ans = min(ans, get<0>(vec2[i]) - root->mn);
	}
	cout << ans;		
}
