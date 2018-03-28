#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int H, N, A[MAXN];
int main() {
	scanf("%d%d", &H, &N);
	for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
	int cur = 0;
	for (int d = 0; d <= H; ++d) {
		for (int p = 0; p < N; ++p) {
			cur += A[p];
			cur = max(0, cur);
			if (cur >= H) {
				printf("%d %d\n", d, p);
				return 0;
			}
		}
	}
	puts("-1 -1");
}