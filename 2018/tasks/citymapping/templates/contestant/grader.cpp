#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

static int N, Q, S, twok[1005][11], depth[1005], curQ, target = 6500;
static long long dist[1005];
static vector< pair<int, int> > adjlist[1005];
static vector< pair< pair<int, int>, int > > edgelist, user_edgelist;

static void dfs(int x, int p, long long d, int dep) {
	dist[x] = d;
	depth[x] = dep;
	twok[x][0] = p;
	for (int i = 1; i <= 10; i++) {
		if (twok[x][i - 1] == -1) break;
		twok[x][i] = twok[twok[x][i - 1]][i - 1];
	}
	for (int i = 0; i < (int)adjlist[x].size(); i++) {
		if (adjlist[x][i].first == p) continue;
		dfs(adjlist[x][i].first, x, d + adjlist[x][i].second, dep + 1);
	}
}

static int lca(int x, int y) {
	if (depth[x] > depth[y]) swap(x, y);
	int dd = depth[y] - depth[x];
	for (int i = 0; i <= 10; i++) if (dd & (1 << i)) y = twok[y][i];
	if (x == y) return x;
	for (int i = 10; i >= 0; i--) {
		if (twok[x][i] != twok[y][i]) {
			x = twok[x][i];
			y = twok[y][i];
		}
	}
	return twok[x][0];
}

long long get_distance(int X, int Y) {
	if (X <= 0 || X > N || Y <= 0 || Y > N) {
		printf("Wrong Answer: get_distance() arguments out of range.\n");
		exit(0);
	}
	curQ++;
	if (curQ > Q) {
		printf("Wrong Answer: Too many calls to get_distance().\n");
		exit(0);
	}
	return dist[X-1] + dist[Y-1] - dist[lca(X-1, Y-1)] * 2;
}
	

int main() {
	if (scanf("%d%d%d", &N, &Q, &S) != 3) {
		printf("Wrong Input Format\n");
		exit(0);
	}
	for (int i = 0; i < N - 1; i++) {
		int a, b, w;
		if (scanf("%d%d%d", &a, &b, &w) != 3) {
			printf("Wrong Input Format\n");
			return 0;
		}
		a--;
		b--;
		adjlist[a].push_back(make_pair(b, w));
		adjlist[b].push_back(make_pair(a, w));
		edgelist.push_back(make_pair(make_pair(min(a, b) + 1, max(a, b) + 1), w));
	}
	sort(edgelist.begin(), edgelist.end());
	memset(twok, -1, sizeof(twok));
	dfs(0, -1, 0, 0);
	int A[N-1], B[N-1], W[N-1];
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
	memset(W, 0, sizeof(W));
	find_roads(N, Q, A, B, W);
	for (int i = 0; i < N-1; i++) user_edgelist.push_back(make_pair(make_pair(min(A[i], B[i]), max(A[i], B[i])), W[i]));
	sort(user_edgelist.begin(), user_edgelist.end());
	if (edgelist != user_edgelist) {
		printf("Wrong Answer: Reported list of edges differ from actual.\n");
		exit(0);
	}
	if (S <= 4) {
		printf("Score: 100.00%%\nCorrect: %d out of %d queries used.\n", curQ, Q);
		exit(0);
	} else {
		if (curQ <= target) printf("Score: 100.00%%\nCorrect: %d out of %d queries used.\n", curQ, Q);
		else if (curQ >= 12000) printf("Score: %.2lf%%\nCorrect: %d out of %d queries used.\n", (10.0-10.0*((double)(curQ - 12000) / 13000)) / 43 * 100, curQ, Q);
		else printf("Score: %.2lf%%\nCorrect: %d out of %d queries used.\n", (40.0-30.0*((double)(curQ - target) / (12000 - target))) / 43 * 100, curQ, Q);
	}
}
