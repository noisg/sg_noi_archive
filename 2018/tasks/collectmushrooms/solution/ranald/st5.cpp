#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
const int INF = 1000000000;
int R, C, D, K;
char G[MAXN];
int main() {
	scanf("%d%d%d%d", &R, &C, &D, &K);
	assert(R == 1);
	scanf("%s", G);
	vector<int> v;
	v.push_back(-INF);
	for (int i = 0; i < C; ++i) {
		if (G[i] == 'S') v.push_back(i);
	}
	v.push_back(INF);
	int ans = 0;
	for (int i = 0; i < C; ++i) {
		if (G[i] != 'M') continue;
		int cnt = upper_bound(v.begin(), v.end(), i+D) - lower_bound(v.begin(), v.end(), i-D);
		if (cnt >= K) ++ans;
	}
	printf("%d\n", ans);
}
