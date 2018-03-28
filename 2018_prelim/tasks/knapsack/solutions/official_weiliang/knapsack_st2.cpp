#include <bits/stdc++.h>
#define MAXN 100004
#define MAXS 2004
using namespace std;
int s,n,w[MAXN];
long long v[MAXN],k[MAXN],dp[MAXS];
int main(){
	scanf("%d %d",&s,&n);
	for(int x=0;x<n;x++){
		scanf("%lld %d %lld",&v[x],&w[x],&k[x]);
		for(int y=s;y>=w[x];y--){
			dp[y]=max(dp[y],dp[y-w[x]]+v[x]);
		}
	}
	long long ans=0;
	for(int x=1;x<=s;x++) ans=max(ans,dp[x]);
	printf("%lld\n",ans);
	return 0;
} 
