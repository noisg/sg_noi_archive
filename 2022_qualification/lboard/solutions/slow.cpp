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
	ll curbst = -1e10;
	REP(i,n) {
		REP(j,m) {
			ll curW = arr[i][j];
			ll bstW = curW;
			REPL(k, j+1, m) {
				curW += arr[i][k];
				bstW = max(curW, bstW);
			}
			curW = arr[i][j];
			for (int k = j-1; k>=0; k--) {
				curW += arr[i][k];
				bstW = max(curW, bstW);
			}
			ll curH = arr[i][j];
			ll bstH = curH;
			REPL(k, i+1, n) {
				curH += arr[k][j];
				bstH = max(bstH, curH);
			}
			curH = arr[i][j];
			for (int k = i-1; k>=0; k--) {
				curH += arr[k][j];
				bstH = max(bstH, curH);
			}
			curbst = max(curbst, bstH+bstW - arr[i][j]);
		}
	}
	
	cout<<curbst<<"\n";
}

int main()
{
  	//...
	solver();

}	
