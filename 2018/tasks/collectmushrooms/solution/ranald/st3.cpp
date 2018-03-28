#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int R, C, D, K;
string G[MAXN];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int main() {
	scanf("%d%d%d%d", &R, &C, &D, &K);
	assert(R <= 100 && C <= 100);
	assert(D == 1);
	assert(K == 1);
	int ans = 0;
	for (int i = 0; i < R; ++i) {
		cin >> G[i];
	}
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (G[i][j] != 'M') continue;
			for (int k = 0; k < 8; ++k) {
				int x = i + dx[k], y = j + dy[k];
				if (x < 0 || y < 0 || x >= R || y >= C) continue;
				if (G[x][y] == 'S') {
					++ans;
					break;
				}
			}
		}
	}
	printf("%d\n", ans);
}
