#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
ll H, N, A[MAXN], sum;
int main() {
	scanf("%lld%lld", &H, &N);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &A[i]);
		sum += A[i];
		if (sum >= H) {
			printf("0 %d\n", i);
			return 0;
		}
	}
	if (sum == 0) {
		puts("-1 -1");
		return 0;
	}
	ll left = H % sum;
	if (left == 0) {
		printf("%lld %d\n", H/sum-1, N-1);
		return 0;
	}
	for (int i = 0; i < N; ++i) {
		left -= A[i];
		if (left <= 0) {
			printf("%lld %d\n", H/sum, i);
			return 0;
		}
	}
}