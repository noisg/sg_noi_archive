#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
ll H, N, A[MAXN];
__int128 sum;
int main() {
	scanf("%lld%lld", &H, &N);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &A[i]);
		sum += A[i];
		sum = max((__int128) 0, sum);
		if (sum >= H) {
			printf("0 %d\n", i);
			return 0;
		}
	}
	if (sum == 0) {
		puts("-1 -1");
		return 0;
	}
	__int128 d1 = sum;
	__int128 high = sum;
	for (int i = 0; i < N; ++i) {
		sum += A[i];
		sum = max((__int128) 0, sum);
		high = max(sum, high);
		if (sum >= H) {
			printf("1 %d\n", i);
			return 0;
		}
	}
	__int128 d2 = sum;
	if (d1 >= d2) {
		puts("-1 -1");
		return 0;
	}
	__int128 step = d2 - d1;
	long long days = (H-high+step-1)/step;
	__int128 left = H-(days*step)-d1;
	if (left == 0) {
		printf("%lld %d\n", days, N-1);
		return 0;
	}
	for (int i = 0; i < N; ++i) {
		left -= A[i];
		if (left <= 0) {
			printf("%lld %d\n", days+1, i);
			return 0;
		}
	}
}