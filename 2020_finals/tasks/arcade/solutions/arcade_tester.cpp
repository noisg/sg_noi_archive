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
pair<int, int> P[1000005];
int f[1000005];
void update(int x,int v){
	for(;x<=1000003;x+=x&(-x))f[x]=max(f[x],v);
}
int query(int x){
	if(x==0)return 0;
	int sum = 0;
	for(;x;x-=x&(-x))sum = max(sum,f[x]);
	return sum;
}
int T[1000005], A[1000005];
vector<int> t;
int main() {
	int N, M;
	N = readInt();
	M = readInt();
	for(int i=0;i<M;i++)T[i] = readInt();
	for(int i=0;i<M;i++)A[i] = readInt();
	int maxn = 0;
	for (int i = 0; i < M; i++){
		P[i] = make_pair(T[i] + A[i], -(A[i] - T[i] + M));
		t.push_back((A[i] - T[i] + M));	
	} 
	sort(t.begin(),t.end());
	sort(P, P + M);
	for (int i = 0; i < M; i++) {
		int pos = lower_bound(t.begin(), t.end(), -P[i].second) - t.begin()+1;
		int a = query(pos-1)+1;
		maxn = max(maxn,a);
		update(pos,a);
	}
	cout<< maxn;
}
