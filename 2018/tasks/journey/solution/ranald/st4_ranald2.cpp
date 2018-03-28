#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int INF = 500000001;
typedef pair<int, int> pi;
int N, M, H;
vector<pi> adjList[MAXN];
int memo[MAXN][405];
int brute(int x, int d) {
	if (d < 0) return 0;
	if (x == N-1) {
		if (d == 0) return 1;
		else return 0;
	}
	if (memo[x][d] != -1) return memo[x][d];
	int res = brute(x, d-1);
	for (auto it:adjList[x]) {
		res += brute(it.first, d - it.second);
		res = min(INF, res);
	}
	return memo[x][d] = res;
}
int main() {
	scanf("%d%d%d", &N, &M, &H);
	for (int i = 0; i < N-1; ++i) {
		for (int j = 0, a, c; j < H; ++j) {
			scanf("%d%d", &a, &c);
			if (a <= i) continue;
			adjList[i].emplace_back(a, c);
		}
	}
	memset(memo, -1, sizeof memo);
	for (int i = 0; i < M; ++i) {
		if (i) printf(" ");
		printf("%d", brute(0, i));
	}
}
