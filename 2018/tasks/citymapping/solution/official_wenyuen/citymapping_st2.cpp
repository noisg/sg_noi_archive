#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

vector< pair< long long, pair<int, int> > > edgelist;
int p[1005];

int fp(int x) {
	if (p[x] == x) return x;
	return p[x] = fp(p[x]);
}

void merge(int x, int y) {
	p[fp(x)] = fp(y);
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			edgelist.push_back(make_pair(get_distance(i + 1, j + 1), make_pair(i, j)));
		}
	}
	sort(edgelist.begin(), edgelist.end());
	int cur = 0;
	for (int i = 0; i < N; i++) p[i] = i;
	for (int i = 0; i < edgelist.size(); i++) {
		if (fp(edgelist[i].second.first) == fp(edgelist[i].second.second)) continue;
		merge(edgelist[i].second.first, edgelist[i].second.second);
		A[cur] = edgelist[i].second.first + 1;
		B[cur] = edgelist[i].second.second + 1;
		W[cur] = edgelist[i].first;
		cur++;
	}
}

