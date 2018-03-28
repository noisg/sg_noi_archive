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
vector<int> choices;

int dfs(int x, int p) {
	int ans = 1;
	choices.push_back(x);
	for (int i = 0; i < child[x].size(); i++) if (!block[child[x][i].first]) ans += dfs(child[x][i].first, x);
	return weight[x] = ans;
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	int myrt = rand() % N;
	for (int i = 0; i < N; i++) {
		if (i != myrt) V.push_back(make_pair(my_query(myrt, i), i));
	}
	sort(V.begin(), V.end());
	
	for (int i = 0; i < V.size(); i++) {
		int newnode = V[i].second;
		long long dist = V[i].first;
		int rt = myrt;
		while (1) {
			vector< pair<int, long long> > V2;
			long long curd = 0;
			choices.clear();
			dfs(rt, -1);
			if (weight[rt] == 1) {
				A[i] = newnode + 1;
				B[i] = rt + 1;
				W[i] = my_query(myrt, newnode) - my_query(myrt, rt);
				child[rt].push_back(make_pair(newnode, W[i]));
				for (int j = 0; j < blocked.size(); j++) block[blocked[j]] = 0;
				blocked.clear();
				break;
			}
			
			int mnd = 1000000000, node = -1;
			for (int j = 0; j < choices.size(); j++) {
				if (max(weight[choices[j]], weight[rt] - weight[choices[j]]) < mnd) {
					mnd = max(weight[choices[j]], weight[rt] - weight[choices[j]]);
					node = choices[j];
				}
			}
			
			long long d = my_query(newnode, node);
			if (d + my_query(myrt, node) == my_query(myrt, newnode)) {
				rt = node;
			} else {
				block[node] = 1;
				blocked.push_back(node);
			}
		}
	}
}
