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
ll brute(int s, int e, int x, int y){
	if(x==2&&y==e)return 1;
	int nx=x,ny=y+1;
	if(y==e)nx=x+1,ny=s;
	if(G[x][y]!='.')return brute(s,e,nx,ny);
	ll res=0;
	res+=brute(s,e,nx,ny); //blank
	if(y<e && G[x][y+1]=='.'){
		char tmp=G[x][y+1];
		G[x][y+1]='n';
		res+=brute(s,e,nx,ny);
		G[x][y+1]=tmp;
	}
	if(x<2 && G[x+1][y]=='.'){
		char tmp=G[x+1][y];
		G[x+1][y]='n';
		res+=brute(s,e,nx,ny);
		G[x+1][y]=tmp;
	}
	return res;
}
ll bruteQuery(int x, int y){
	return brute(x,y,0,x);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>N>>Q;	
	FOR(i,0,2)cin>>(G[i]+1);
	while(Q--){
		int op;cin>>op;
		assert(op==1||op==2);
		if(op==1){
			int x,y;cin>>x>>y; //1-indexed
			assert(1<=x&&x<=3&&1<=y&&y<=N);
			G[x-1][y]^=('.'^'x');
		}
		else{
			int a,b;cin>>a>>b;
			assert(1<=a&&a<=b&&b<=N);
			cout<<bruteQuery(a,b)<<"\n";
		}
	}
}
/*
9 9
.........
.........
.........
2 1 9
2 1 9
2 1 9
2 1 9
2 1 9
2 1 9
2 1 9
2 1 9
2 1 9


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
