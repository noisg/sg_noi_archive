#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll val[1005];
ll arr[5005],arr2[5005];
ll dp[2][5005][4],ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll x,y,z,n,m,a,b,c,d,i,j,k;
	cin>>k>>n>>m>>x>>y;
	x = -x;
	y = -y;
	ans = -x-y*m;
	for(i=0;i<k;i++)cin>>val[i+1];
	for(i=1;i<=n;i++)cin>>arr[i];
	for(i=1;i<=m;i++)cin>>arr2[i];
	for(i=1;i<=m;i++){
		dp[0][i][0] = -2e9;
		dp[0][i][1] = -2e9;
		dp[0][i][3] = -2e9;
		dp[0][i][2] = -x-y*i;
	}
		dp[0][0][0] = -2e9;
		dp[0][0][1] = -2e9;
		dp[0][0][2] = -2e9;
		dp[0][0][3] = 0;
		dp[1][0][0] = -2e9;
		dp[1][0][1] = -2e9;
		dp[1][0][2] = -2e9;
		dp[1][0][3] = 0;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			dp[i%2][j][0] = max({-x-y*j,max(dp[i%2][j-1][0],dp[(i-1)%2][j][0])-y,max(dp[(i-1)%2][j][2],dp[i%2][j-1][1])-x-y});
			dp[i%2][j][1] = max({dp[(i-1)%2][j][1]-y,dp[(i-1)%2][j][3]-x-y});
			dp[i%2][j][2] = max({dp[i%2][j-1][2]-y,dp[i%2][j-1][3]-x-y,-x-y*j});
			if(arr[i]==arr2[j]){
				dp[i%2][j][3] = val[arr[i]]+max({dp[(i-1)%2][j-1][0],dp[(i-1)%2][j-1][1],dp[(i-1)%2][j-1][2],dp[(i-1)%2][j-1][3]});
			}else dp[i%2][j][3] = -2e9;
//			cout<<i<<" "<<j<<" states: \n";
//			for(k=0;k<4;k++)cout<<dp[i][j][k]<<" "<<k/2<<k%2<<'\n';
		}
		for(j=0;j<4;j++)ans = max(ans,dp[i%2][m][j]);
	}
	cout<<ans;
}
