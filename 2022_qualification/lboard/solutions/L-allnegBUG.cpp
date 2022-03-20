#define REP(i, n) for(int i = 0; i < n; i ++)
#define REPL(i,m, n) for(int i = m; i < n; i ++)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define SORT(arr) sort(arr.begin(), arr.end())
#define REV(arr) reverse(arr.begin(), arr.end())
#define LSOne(S) ((S)&-(S))
#define M_PI 3.1415926535897932384
#define INF 999999999
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;
void solver() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int n,m;cin>>n>>m;
	vvll arr(n, vll(m));
	REP(i, n) {
		REP(j, m) {
			cin>>arr[i][j];
		}
	}
	auto generateKadane = [](vll &arr) {
		vll res;
		ll cur = 0;
		for (auto x: arr) {
			res.push_back(cur + x);
			cur += x;
			cur = max(cur, 0LL);
		}
		return res;
	};
	vvll hori1;
	vvll hori2;
	vvll verti1;
	vvll verti2;
	REP(i, n) {
		vll curarr = arr[i];
		vll h1 = generateKadane(curarr);
		hori1.push_back(h1);
		REV(curarr);
		vll h2 = generateKadane(curarr);
		REV(h2);
		hori2.push_back(h2);
	}
	REP(j, m) {
		vll curarr;
		REP(i,n) {
			curarr.push_back(arr[i][j]);
		}
		vll v1 = generateKadane(curarr);
		verti1.push_back(v1);
		REV(curarr);
		vll v2 = generateKadane(curarr);
		REV(v2);
		verti2.push_back(v2);
	}
	ll curbst = 0;
	REP(i, n) {
		REP(j, m) {
			ll bstH = max(hori1[i][j], hori2[i][j]);
			ll bstV = max(verti1[j][i], verti2[j][i]);
			curbst = max(curbst, bstH + bstV - arr[i][j]);
		}
	}
	cout<<curbst;
}
int main()
{
  	//...
	solver();
}	
