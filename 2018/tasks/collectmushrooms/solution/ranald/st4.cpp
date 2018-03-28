#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
int R, C, D, K;
string G[MAXN];
int main() {
	scanf("%d%d%d%d", &R, &C, &D, &K);
	assert(R <= 500 && C <= 500);
	int ans = 0;
	for (int i = 0; i < R; ++i) {
		cin >> G[i];
	}
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (G[i][j] != 'M') continue;
			int cnt = 0;
			for (int x = max(0, i-D); x <= min(R-1, i+D); ++x) {
				for (int y = max(0, j-D); y <= min(C-1, j+D); ++y) {
					if (G[x][y] == 'S') ++cnt;
				}
			}
			if (cnt >= K) ++ans;
		}
	}
	printf("%d\n", ans);
}
