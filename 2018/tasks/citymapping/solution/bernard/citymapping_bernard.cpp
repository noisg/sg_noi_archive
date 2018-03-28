#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

int curQ;
map< pair<int, int>, long long > memo;

long long my_query(int x, int y) {
	if (x == y) return 0;
	if (x > y) swap(x, y);
	if (memo.find(make_pair(x, y)) == memo.end()) {
		curQ++;
		return memo[make_pair(x, y)] = get_distance(x+1, y+1);
	}
	else return memo[make_pair(x, y)];
}

int weight[1005];
vector< pair<int, int> > child[1005];
vector< pair<long long, int> > V;
vector<int> blocked;
bool block[1005];

int dfs(int x, int p) {
	int ans = 1;
	for (int i = 0; i < child[x].size(); i++) if (!block[child[x][i].first]) ans += dfs(child[x][i].first, x);
	return weight[x] = ans;
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	int myrt = 0;
	for (int i = 0; i < N; i++) {
		if (i != myrt) V.push_back(make_pair(my_query(myrt, i), i));
	}
	sort(V.begin(), V.end());
	
	for (int i = 0; i < V.size(); i++) {
		int newnode = V[i].second;
		long long dist = V[i].first;
		int rt = myrt;
		//printf("joining node %d\n",newnode);
		while (1) {
			vector< pair<int, long long> > V2;
			long long curd = 0;
			dfs(rt, -1);
			//printf("%d\n", rt);
			if (weight[rt] == 1) {
				A[i] = newnode + 1;
				B[i] = rt + 1;
				W[i] = my_query(myrt, newnode) - my_query(myrt, rt);
				//printf("%d %d\n", rt, newnode);
				child[rt].push_back(make_pair(newnode, W[i]));
				for (int j = 0; j < blocked.size(); j++) block[blocked[j]] = 0;
				blocked.clear();
				break;
			}
			int leaf = rt;
			V2.push_back(make_pair(rt, 0));
			while (child[leaf].size() > 0) {
				int mx = -1, mxnode = myrt;
				for (int i = 0; i < child[leaf].size(); i++) {
					if (block[child[leaf][i].first]) continue;
					if (weight[child[leaf][i].first] > mx) {
						mx = weight[child[leaf][i].first];
						mxnode = i;
					}
				}
				if (mx == -1) break;
				//printf("%d!\n", mxnode);
				curd += child[leaf][mxnode].second;
				leaf = child[leaf][mxnode].first;
				
				V2.push_back(make_pair(leaf, curd));
			}
			long long bc = my_query(leaf, newnode);
			long long ab = my_query(myrt, leaf) - my_query(myrt, rt);
			long long ac = my_query(myrt, newnode) - my_query(myrt, rt);
			long long sum = (bc + ab + ac) / 2;
			long long a = sum - bc, b = sum - ac, c = sum - ab;
			for (int j = 0; j < V2.size(); j++) {
				if (V2[j].second == a) {
					rt = V2[j].first;
					if (j+1 != V2.size()) {
						block[V2[j+1].first] = 1;
						blocked.push_back(V2[j+1].first);
					}
					break;
				}
			}
		}
	}
	
	/* check degrees */
	int degree[N];
	memset(degree, 0, sizeof(degree));
	for (int i = 0; i < N-1; i++) {
		degree[A[i]-1]++;
		degree[B[i]-1]++;
	}
	for (int i = 0; i < N; i++) assert(degree[i] <= 3);
}
