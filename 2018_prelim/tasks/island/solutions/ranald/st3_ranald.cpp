#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1004;
int N, M, fac[MAXN];
bitset<MAXN> adjMat[MAXN];
int main() {
	scanf("%d%d", &N, &M);
	assert(N + M <= 1000);
	for (int i = 0, u, v; i < N+M-1; ++i) {
		scanf("%d%d", &u, &v);
		adjMat[u][v] = 1;
		adjMat[v][u] = 1;
	}
	for (int i = 1; i <= N+M; ++i) {
		int cnt = 0;
		for (int k = 1; k <= N+M; ++k) {
			cnt += adjMat[i][k];
		}
		fac[cnt-1]++;
	}
	for (int i = N+M-1; i >= 1; --i) {
		if (fac[i] > 0) {
			printf("%d %d\n", i, fac[i]);
			fac[i-1] += fac[i];
		}
	}

}
