#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pi;
const int MAXN=30005;
const int MOD=1000000007;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define DEC(i,a,b) for(int i=(a);i>=(b);i--)
#define fst first
#define snd second
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v).size())
#define db(x) cerr<<#x<<" = "<<x<<"\n"

int N,Q;
char G[3][MAXN];
int B[MAXN];
ll dp[MAXN][8];
#define prv dp[i-1]
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>N>>Q;
	cin>>(G[0]+1)>>(G[1]+1)>>(G[2]+1);
	FOR(i,0,2)FOR(j,1,N)if(G[i][j]=='x')assert(false);
	dp[0][0]=1;
	FOR(i,1,7)dp[0][i]=0;
	FOR(i,1,N){
		dp[i][0]=(prv[0]*3+prv[1]*2+prv[2]+prv[3]+prv[4]*2+prv[5]+prv[6]+prv[7])%MOD;
		dp[i][1]=(prv[0]*2+prv[2]+prv[4]+prv[6])%MOD;
		dp[i][2]=(prv[0]+prv[1]+prv[4]+prv[5])%MOD;
		dp[i][3]=(prv[0]+prv[4])%MOD;
		dp[i][4]=(prv[0]*2+prv[1]+prv[2]+prv[3])%MOD;
		dp[i][5]=(prv[0]+prv[2])%MOD;
		dp[i][6]=(prv[0]+prv[1])%MOD;
		dp[i][7]=prv[0];
	}
	while(Q--){
		int op;cin>>op;
		assert(op==2);
		int a,b;cin>>a>>b;
		assert(1<=a&&a<=b&&b<=N);
		cout<<dp[b-a+1][0]<<"\n";
	}
}
/*
0:
3 2 1 1 2 1 1 1
2 0 1 0 1 0 1 0
1 1 0 0 1 1 0 0
1 0 0 0 1 0 0 0
2 1 1 1 0 0 0 0
1 0 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
1:
2 0 1 0 1 0 1 0
0 0 0 0 0 0 0 0
1 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0
1 0 1 0 0 0 0 0
0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
2:
1 1 0 0 1 1 0 0
1 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
3:
1 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
4:
2 1 1 1 0 0 0 0
1 0 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
5:
1 0 1 0 0 0 0 0
0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
6:
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
7:
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0

4 3
.x.x
xx..
...x
2 1 4
1 2 3 2 4
2 1 4
Ans:
11
3

2 1
..
..
xx
2 1 2
Ans:
7

14 5
.x.xx.x...x..x
.x..x..x.x..xx
...x..xxx....x
1 1 14
1 3 6
2 1 4 2 5
1 1 14
1 3 6
Ans:
30044
20

10 10
.x.x.x.xx.
.x...x...x
.x.x....x.
2 3 10
1 3 2 3 7
2 3 10
2 4 9
2 1 6
1 2 4 2 9
2 5 10
1 1 1 2 3
1 1 3 1 4
1 1 3 3 7
*/
