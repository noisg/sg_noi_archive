#include<bits/stdc++.h>
using namespace std;
struct node{
	int s, e, m, cnt;
	node *l, *r;
	node(int _s, int _e): s(_s), e(_e), m((_s+_e)/2), cnt(0){
		if(s == e) return;
		l = new node(s, m);
		r = new node(m+1, e);
	}
	void update(int x, int v){
		cnt += v;
		if(s == e) return;
		if(x <= m) l->update(x, v);
		else r->update(x, v);
	}
	int query(int x, int y){
		if(x <= s && y >= e) return cnt;
		int ret = 0;
		if(x <= m) ret += l->query(x, y);
		if(y >= m+1) ret += r->query(x, y);
		return ret;
	}
	void clear(){
		cnt = 0;
		if(s == e) return;
		l->clear();
		r->clear();
	}
};

long long invLeft[300001], invRight[300001];
pair<long long, int> disArr[300001];
int cnt = 1;
long long solve(int n, long long H[]){
	for(int i = 1; i <= n; i++) disArr[i] = {H[i], i};
	sort(disArr + 1, disArr + n + 1);

	for(int i = 1; i <= n; i++){
		if (i > 1 && disArr[i].first != disArr[i-1].first) cnt++;
		H[disArr[i].second] = cnt;
	}
	
	node *root = new node(0, n);
	for(int i = 1; i <= n; i++){
		invLeft[i] = root->query(0, H[i] - 1);
		root->update(H[i], 1);
	}
	
	root->clear();
	for(int i = n; i > 0; i--){
		invRight[i] = root->query(0, H[i] - 1);
		root->update(H[i], 1);
	}
	
	long long total = 0;
	for(int i = 1; i <= n; i++){
		total += invLeft[i] * invRight[i];
	}
	
	return total;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	long long H[300001];
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> H[i];
	long long total = solve(n, H);
	cout << total;
	return 0;
}
