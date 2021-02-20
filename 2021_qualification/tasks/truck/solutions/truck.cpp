#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll f[3][100005],p[100005][20],num[100005],hi[100005],dfscnt = 1,depth[100005],dist[100005],val[100005];
vector<tuple<ll,ll,ll> > aj[100005];
ll mod = 1e9+7;

ll query(ll idx, ll x){
	if(x==0)return 0;
	ll sum = 0;
	for(;x;x-=x&(-x)){
		sum+=f[idx][x];
		sum%=mod;
	}
	return sum;
}

void update(ll idx, ll x,ll v){
    v%=mod;
	for(;x<=100003;x+=x&(-x)){
		f[idx][x]+=v;
		f[idx][x]%=mod;	
	}
}

void rupdate(ll idx,ll x,ll y, ll v){
    v%=mod;
	update(idx,x,v);
	update(idx,y+1,-v);
}

ll rquery(ll idx,ll x,ll y){
	return (query(idx,y)-query(idx,x))%mod;
}

void add(ll x,ll par){
	p[x][0] = par;
	for(int i=0;i<18;i++)
		if(p[x][i]!=-1&&p[p[x][i]][i]!=-1)p[x][i+1] = p[p[x][i]][i];
}

void dfs(ll x,ll par,ll w){
	num[x] = hi[x] = dfscnt++;
	add(x,par);
	if(par!=-1){
		val[x] = w;
		depth[x] = depth[par]+1;
	}
	for(auto v:aj[x]){
		ll u,d,c;
		tie(u,d,c) = v;
		if(u==par)continue;
		dist[u] = dist[x] + d;
		dist[u]%=mod;
		dfs(u,x,c);
		hi[x] = max(hi[x],hi[u]);
	}
	if(par!=-1){
		rupdate(0,num[x],hi[x],(w*dist[x])%mod);
		rupdate(1,num[x],hi[x],(w*dist[par])%mod);
		rupdate(2,num[x],hi[x],w);		
	}
}

ll lca(ll x,ll y){
	if(depth[x]<depth[y])swap(x,y);
	for(int i=19;i>=0;i--){
		if(p[x][i]!=-1&&depth[p[x][i]]>=depth[y])x = p[x][i];
	}
	if(x==y)return x;
	for(int i=19;i>=0;i--){
		if(p[x][i]!=-1&&p[x][i]!=p[y][i]){
			x = p[x][i];
			y = p[y][i];
		}
	}
	return p[x][0];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n,m,q,i,j,k,a,b,c,x,sum,d;
	memset(p,-1,sizeof(p));
	cin>>n>>m;
	for(i=0;i<n-1;i++){
		cin>>a>>b>>d>>c;
		aj[a].emplace_back(b,d,c);
		aj[b].emplace_back(a,d,c);
	}
	dfs(1,-1,0);
	cin>>q;
	while(q--){
		cin>>a;
		if(a==0){
			cin>>a>>b>>c;
			if(depth[a]<depth[b])swap(a,b);
			rupdate(0,num[a],hi[a],(c - val[a])*dist[a]);
			rupdate(1,num[a],hi[a],(c - val[a])*dist[b]);
			rupdate(2,num[a],hi[a],c - val[a]);
			val[a] = c;
		}else{
			cin>>a>>b;
			c = lca(a,b);
			x = dist[a]+dist[b]-2*dist[c];
			x%=mod;
			sum = (x*m)%mod;
			sum += (rquery(2,num[c],num[a])*dist[a])%mod;
			sum%=mod;
			sum-=rquery(0, num[c],num[a]);
			sum%=mod;
			sum += (rquery(2,num[c],num[b])*(x-dist[b]))%mod;
			sum %= mod;
			sum += rquery(1, num[c],num[b]);
			sum%=mod;
			sum+=mod;
			sum%=mod;
			cout<<sum<<"\n";
		}
	}
}
