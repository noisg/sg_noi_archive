#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200004;
int N, M, cnt[MAXN], fac[MAXN];
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, u, v; i < N+M-1; ++i) {
		scanf("%d%d", &u, &v);
		if (cnt[u-1]++ > 1) 
		printf("%d 1\n", cnt[u-1]-1);
		if (cnt[v-1]++ > 1)
		printf("%d 1\n", cnt[v-1]-1);
	}
}
