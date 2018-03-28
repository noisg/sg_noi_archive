#include <bits/stdc++.h>
#define MAXN 100004
#define MAXS 2004
using namespace std;
int s,n,w[MAXN];
long long v[MAXN],k[MAXN],dp[MAXS];
typedef pair<int,int> ii;
priority_queue <ii> pq[MAXS];
int main(){
	scanf("%d %d",&s,&n);
	for(int x=0;x<n;x++){
		scanf("%lld %d %lld",&v[x],&w[x],&k[x]);
		pq[w[x]].push(make_pair(v[x],k[x]));
	}
	for(int x=1;x<=s;x++){
		long long cnt=s/x;
		while(!pq[x].empty()&&cnt){
			ii i=pq[x].top();
			pq[x].pop();
			if(i.second>cnt) i.second=cnt;
			cnt-=i.second;
			for(int y=0;y<i.second;y++)	for(int z=s;z>=x;z--) dp[z]=max(dp[z],dp[z-x]+i.first);
		}
	}
	long long ans=0;
	for(int x=1;x<=s;x++) ans=max(ans,dp[x]);
	printf("%lld\n",ans);
	return 0;
} 
