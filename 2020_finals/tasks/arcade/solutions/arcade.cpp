#include <bits/stdc++.h>
using namespace std;
inline int readInt() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
    return x;
}
pair<int, int> P[2000005];
vector<int> V;
int T[2000005], A[2000005];
int main() {
	int N, M;
	N = readInt();
	M = readInt();
	for(int i=0;i<M;i++)T[i] = readInt();
	for(int i=0;i<M;i++)A[i] = readInt();
	for (int i = 0; i < M; i++) P[i] = make_pair(T[i] + A[i], -(A[i] - T[i] + M));
	sort(P, P + M);
	for (int i = 0; i < M; i++) {
		int pos = lower_bound(V.begin(), V.end(), -P[i].second) - V.begin();
		if (pos == V.size()) V.push_back(-P[i].second);
		else V[pos] = -P[i].second;
	}
	cout<< V.size();
}
