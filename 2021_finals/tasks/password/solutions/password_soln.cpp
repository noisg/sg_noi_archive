#include <bits/stdc++.h>

using namespace std;
typedef long long int li;
typedef pair<int,int> pii;
typedef pair<li,li> pll;
#define mp make_pair
#define pb push_back

long long n, k, a[300005], b[300005], c[300005];
pll p[300005];

long long st[1<<20], sz = 1<<19, d[1<<20];
long long h = 19;

void apply(li p, li value){
	st[p] += value;
	if (p<sz) d[p] += value;
}

void build(li p){
	for (p/=2; p>0; p/=2){
		st[p] = min(st[2*p], st[2*p+1]) + d[p];
	}
}

void push(li p){
	for (li s = h; s>0; s--){
		li i = p >> s;
		if (d[i]!=0){
			apply(i*2, d[i]);
			apply(2*i+1, d[i]);
			d[i] = 0;
		}
	}
}

void inc(li l, li r, li val){
	l+=sz, r+=sz;
	li l0 = l, r0 = r;
	for (; l<r; l/=2, r/=2){
		if (l&1) apply(l++, val);
		if (r&1) apply(--r, val);
	}
	build(l0);
	build(r0-1);
}

li query(li l, li r){
	l+=sz, r+=sz;
	li ans = 2e18;
	push(l);
	push(r-1);
	for (; l<r; l/=2, r/=2){
		if (l&1) ans = min(ans, st[l++]);
		if (r&1) ans = min(ans, st[--r]);
	}
	return ans;
}


int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	k++;
	
	for (int i=1; i<=n; i++) cin >> a[i];
	for (int i=1; i<=n; i++) cin >> b[i];
	for (int i=1; i<=n; i++) a[i] = (a[i] + k - b[i]) % k;
	
	long long sum = 0;
	for (int i=0; i<=n; i++){
		c[i] = (a[i+1] - a[i] + k) % k;
		p[i] = mp(c[i], -i);
		sum += k - c[i];
		inc(i, i+1, sum);
	}
	
	sort(p, p+n+1);
	
	for (int i=0; i<=n; i++){
		long long z = p[i].first, y = -p[i].second;
		long long x = k - z;
		inc(y, n+1, -k);
		long long t = query(0, n+1);
		if (t < 0) inc(y, n+1, k);
		else sum += k - 2 * x;
	}
	
	cout << sum / 2;
}