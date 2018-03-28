#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int R, C, D, K;
string G[MAXN];
int main() {
	scanf("%d%d%d%d", &R, &C, &D, &K);
	assert(K == 1);
	assert(D == max(R, C));
	int ans = 0;
	bool ok = 0;
	for (int i = 0; i < R; ++i) {
		cin >> G[i];
		for (int j = 0; j < G[i].length(); ++j) {
			if (G[i][j] == 'S') ok = 1;
			if (G[i][j] == 'M') ++ans;
		}
	}
	if (ok) printf("%d\n", ans);
	else printf("0\n");
}
