#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200004;
int N, M, cnt[MAXN], fac[MAXN];
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, u, v; i < N+M-1; ++i) {
		scanf("%d%d", &u, &v);
		cnt[u-1]++;
		cnt[v-1]++;
	}
	for (int i = 0; i < N+M; ++i) {
		for (int k = 2; k < cnt[i]; ++k) {
			printf("%d 1\n", k);
		}
	}

}
