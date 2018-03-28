#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	long long mxd = -1;
	int mxnode = 0;
	for (int i = 1; i < N; i++) {
		long long d = get_distance(1, i+1);
		if (d > mxd) {
			mxd = d;
			mxnode = i;
		}
	}
	vector< pair<long long, int> > V;
	for (int i = 0; i < N; i++) {
		V.push_back(make_pair(get_distance(mxnode+1, i+1), i));
	}
	sort(V.begin(), V.end());
	for (int i = 0; i < N - 1; i++) {
		A[i] = V[i].second + 1;
		B[i] = V[i+1].second + 1;
		W[i] = V[i+1].first - V[i].first;
	}
}
