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
/*
node(s,e,b1,b2) counts no. of ways for [s,e] where b1 is restriction on column s due to
previous columns, while b2 is how column e+1 must look due to tiles jutting out, where some
of each tile is in column e
*/

int N,Q;
char G[3][MAXN];
int ans[8],res[8];

void copy(int (&a)[8][8], int (&b)[8][8]){ //a=b
	FOR(i,0,7)FOR(j,0,7)a[i][j]=b[i][j];
}

int tmp[8][8]; //temporary matrix for calculations
inline void mult(int (&res)[8][8], int (&a)[8][8], int (&b)[8][8]){ // res=a*b
    FOR(i,0,7){
        FOR(j,0,7){
            tmp[i][j] = 0;
            FOR(k,0,7)
                tmp[i][j]=(tmp[i][j]+(ll)a[i][k]*b[k][j]%MOD)%MOD;
        }
    }
    swap(res,tmp);
}
int rec[8][8][8]; //recurrence matrix

int getMask(int n){
	return (G[0][n]=='x')|((G[1][n]=='x')<<1)|((G[2][n]=='x')<<2);
}
int t[4*MAXN][8][8];
void build(int id, int s, int e){
	if(s==e){
		copy(t[id],rec[getMask(s)]);
		return;
	}
	int m=(s+e)>>1;
	build(2*id,s,m);
	build(2*id+1,m+1,e);
	mult(t[id], t[2*id], t[2*id+1]);
}
void rflip(int id, int s, int e, int x){
	if(s==x&&e==x){
		copy(t[id],rec[getMask(s)]);
		return;
	}
	int m=(s+e)>>1;
	if(x<=m)rflip(2*id,s,m,x);
	else rflip(2*id+1,m+1,e,x);
	mult(t[id], t[2*id], t[2*id+1]);
}
void query(int id, int s, int e, int x, int y){
	if(s==x&&e==y){
		FOR(j,0,7)res[j]=0;
		FOR(i,0,7)FOR(j,0,7)res[j]=(res[j]+(ll)t[id][i][j]*ans[i]%MOD)%MOD;
		FOR(j,0,7)ans[j]=res[j];
		return;
	}
	int m=(s+e)>>1;
	if(x<=m)query(2*id,s,m,x,min(m,y));
	if(y>m)query(2*id+1,m+1,e,max(m+1,x),y);
}
ll segQuery(int x, int y){
	ans[0]=1;FOR(j,1,7)ans[j]=0;
	query(1,1,N,x,y);
	return ans[0];
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	//Generate transition matrix from column c-1 to c
	FOR(bm,0,7){ //bm is the bitmask for the current column c
		FOR(i,0,7){ //i is the bitmask of the part that juts out from column c-1 into c
			FOR(j,0,7){ //j is the bitmask of the part that juts out from column c to c+1
				rec[bm][i][j]=0;
				if(i&bm)continue; //collision between previous jut-out and current column
				if((i|bm)&j)continue; //collision between (previous jut-out and current column) and tiles required to jut out into next column
				int b=(i|bm|j); //only vertical tiles can be placed in b
				rec[bm][i][j]++; //no vertical tiles placed
				if(!(b&3))rec[bm][i][j]++; //vertical tile placed in rows 0 and 1
				if(!(b&6))rec[bm][i][j]++; //vertical tile placed in rows 1 and 2
			}
		}
	}
	
	cin>>N>>Q;
	FOR(i,0,2)cin>>(G[i]+1);
	build(1,1,N);
	while(Q--){
		int op;cin>>op;
		assert(op==1||op==2);
		if(op==1){
			int x,y;cin>>x>>y;
			assert(1<=x&&x<=3&&1<=y&&y<=N);
			G[x-1][y]^=('.'^'x');
			rflip(1,1,N,y);
		}
		else{
			int a,b;cin>>a>>b; //1-indexed
			assert(1<=a&&a<=b&&b<=N);
			cout<<segQuery(a,b)<<"\n";
		}		
	}
}
/*
4 3
.x.x
xx..
...x
2 1 4
1 2 3
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
2 1 14
2 3 6
1 1 4
2 1 14
2 3 6

14 5
.x.xx.x...x..x
.x..x..x.x..xx
...x..xxx....x
2 1 14
2 3 6
1 1 4 1 4
2 1 14
2 3 6
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
