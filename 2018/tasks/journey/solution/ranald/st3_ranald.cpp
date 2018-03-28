#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int INF = 500000001;
typedef pair<int, int> pi;
int N, M, H;
vector<pi> adjList[MAXN];
int dp[MAXN][405];
int main() {
	scanf("%d%d%d", &N, &M, &H);
	assert(N <= 10000 && M <= 400 && H <= 100);
	for (int i = 0; i < N-1; ++i) {
		for (int j = 0, a, c; j < H; ++j) {
			scanf("%d%d", &a, &c);
			if (a <= i) continue;
			adjList[a].emplace_back(i, c);
		}
	}
	dp[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int k = 0; k < M; ++k) {
			for (auto it:adjList[i]) {
				if (k - it.second < 0) continue;
				for (int k2 = 0; k2 <= k-it.second; ++k2) {
					dp[i][k] += dp[it.first][k2];
					dp[i][k] = min(dp[i][k], INF);
				}
			}
		}
	}
	
	for (int k = 0; k < M; ++k) {
		if (k) printf(" ");
		printf("%d", dp[N-1][k]);
	}
	puts("");
}
