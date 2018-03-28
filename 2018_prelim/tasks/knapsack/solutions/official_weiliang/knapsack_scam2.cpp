#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plpl;
ll N, S;
const int MAXN = 100004;
plpl A[MAXN];
bool cmp1 (plpl a, plpl b) {
	return a.second.first*b.second.second > b.second.first*a.second.second;
}
ll scam1(ll s) {
	sort(A, A+N, cmp1);
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ll k = min(A[i].first, S/A[i].second.second);
		ans += k*A[i].second.first;
		s -= k*A[i].second.second;
	}
	return ans;
}
bool cmp2 (plpl a, plpl b) {
	return a.second.first > b.second.first;
}
ll scam2 (ll s) {
	sort(A, A+N, cmp1);
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i].second.second > S) continue;
		ll k = min(A[i].first, S/A[i].second.second);
		ans += k*A[i].second.first;
		s -= k*A[i].second.second;
	}
	return ans;
}
bool cmp3 (plpl a, plpl b) {
	return a.second.second < b.second.second;
}
ll scam3 (ll s) {
	sort(A, A+N, cmp1);
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i].second.second > S) continue;
		ll k = min(A[i].first, S/A[i].second.second);
		ans += k*A[i].second.first;
		s -= k*A[i].second.second;
	}
	return ans;
}
int main() {
	scanf("%lld%lld", &S, &N);
	for (int i = 0; i < N; ++i) {
		//V, W, K
		scanf("%lld%lld%lld", &A[i].second.first, &A[i].second.second, &A[i].first);
	}
	
	printf("%lld\n", min({scam1(S), scam2(S), scam3(S)}));
}
