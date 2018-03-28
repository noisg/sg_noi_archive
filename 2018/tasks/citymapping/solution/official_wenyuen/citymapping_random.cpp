#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

long long rootdist[1005], leafdist[1005];
map< pair<int, int>, long long > memo;
vector< pair< pair<int, int>, int > > edgelist;

long long my_query(int x, int y) {
	if (x == y) return 0;
	if (x > y) swap(x, y);
	if (memo.find(make_pair(x, y)) == memo.end()) return memo[make_pair(x, y)] = get_distance(x+1, y+1);
	else return memo[make_pair(x, y)];
}

void search(vector< pair<long long, int> > V) {
	int r = (int)V.size() - 1 - rand() % min(5, (int)V.size());
	int endnode = V[r].second;
	for (int i = 0; i < V.size(); i++) rootdist[V[i].second] = V[i].first;
	for (int i = 0; i < V.size(); i++) {
		leafdist[V[i].second] = my_query(V[i].second, V[r].second);
	}
	vector< pair<long long, int> > trunknodes;
	map< long long, vector< pair<long long, int> > > trunkdistance;
	for (int i = 0; i < V.size(); i++) {
		long long ab = rootdist[endnode];
		long long bc = leafdist[V[i].second];
		long long ac = rootdist[V[i].second];
		long long sum = (ab + bc + ac) / 2;
		long long a = sum - bc, b = sum - ac, c = sum - ab;
		if (c == 0) trunknodes.push_back(make_pair(a, V[i].second));
		trunkdistance[a].push_back(make_pair(c, V[i].second));
	}
	sort(trunknodes.begin(), trunknodes.end());
	for (int i = 0; i < (int)trunknodes.size() - 1; i++) {
		edgelist.push_back(make_pair(make_pair(trunknodes[i].second, trunknodes[i+1].second), trunknodes[i+1].first - trunknodes[i].first));
	}
	for (map< long long, vector< pair<long long, int> > >::iterator it = trunkdistance.begin(); it != trunkdistance.end(); it++) {
		if (it->second.size() == 1) continue;
		search(it->second);
	}
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	srand(clock());
	int myrt = rand() % N;
	vector< pair<long long, int> > V;
	for (int i = 0; i < N; i++) {
		V.push_back(make_pair(my_query(myrt, i), i));
	}
	search(V);
	for (int i = 0; i < edgelist.size(); i++) {
		A[i] = edgelist[i].first.first + 1;
		B[i] = edgelist[i].first.second + 1;
		W[i] = edgelist[i].second;
	}
}
