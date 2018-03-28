#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int R, C, D, K;
string G[MAXN];
int main() {
	scanf("%d%d%d%d", &R, &C, &D, &K);
	assert(D == max(R, C));
	assert(R <= 100 && C <= 100);
	int ans = 0, s = 0;
	for (int i = 0; i < R; ++i) {
		cin >> G[i];
		for (int j = 0; j < G[i].length(); ++j) {
			if (G[i][j] == 'S') ++s;
			if (G[i][j] == 'M') ++ans;
		}
	}
	if (s >= K) printf("%d\n", ans);
	else printf("0\n");
}
