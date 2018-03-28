#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
ll H, N, A[MAXN];
int main() {
	scanf("%lld%lld", &H, &N);
	for (int i = 0; i < N; ++i) scanf("%lld", &A[i]);
	ll cur = 0;
	for (ll d = 0; d <= H; ++d) {
		for (int p = 0; p < N; ++p) {
			cur += A[p];
			cur = max(0ll, cur);
			if (cur >= H) {
				printf("%lld %d\n", d, p);
				return 0;
			}
		}
	}
	puts("-1 -1");
}