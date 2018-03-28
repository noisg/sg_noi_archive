#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plpl;
ll N, S;
const int MAXN = 100004;
plpl A[MAXN];
bool cmp (plpl a, plpl b) {
	return a.second.first*b.second.second > b.second.first*a.second.second;
}
int main() {
	scanf("%lld%lld", &S, &N);
	for (int i = 0; i < N; ++i) {
		//V, W, K
		scanf("%lld%lld%lld", &A[i].second.first, &A[i].second.second, &A[i].first);
	}
	sort(A, A+N, cmp);
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ll k = min(A[i].first, S/A[i].second.second);
		ans += k*A[i].second.first;
		S -= k*A[i].second.second;
	}
	printf("%lld\n", ans);
}
