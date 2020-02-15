#include<bits/stdc++.h>
using namespace std;
int fw[300001], cnt = 1;
void update(int x, int v){
	for(; x <= cnt; x += x&-x) fw[x] += v;
}
int query(int x){
	int ret = 0;
	for(; x; x -= x&-x) ret += fw[x];
	return ret;
}

long long invLeft[300001], invRight[300001];
pair<long long, int> disArr[300001];
long long solve(int n, long long H[]){
	for(int i = 1; i <= n; i++) disArr[i] = {H[i], i};
	sort(disArr + 1, disArr + n + 1);

	for(int i = 1; i <= n; i++){
		if (i > 1 && disArr[i].first != disArr[i-1].first) cnt++;
		H[disArr[i].second] = cnt;
	}
	
	for(int i = 1; i <= n; i++){
		invLeft[i] = query(H[i] - 1);
		update(H[i], 1);
	}
	
	fill(fw, fw + n + 1, 0);
	for(int i = n; i > 0; i--){
		invRight[i] = query(H[i] - 1);
		update(H[i], 1);
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
