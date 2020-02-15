#include <bits/stdc++.h>

using namespace std;
typedef long long int li;
typedef pair<int,int> pii;
typedef pair<li,li> pll;
#define mp make_pair
#define pb push_back

int k, n, m, a, b;
int v[1005], s[10005], t[10005];
int dp[3][10005]; //max happiness -idx*b 
int dp1[3][10005], dp2[3][10005], dp3[3][10005];
int ans = 0;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> k >> n >> m >> a >> b;
	a = -a;
	b = -b;
	for (int i=0; i<k; i++){
		cin >> v[i+1];	
	}
	for (int i=2; i<n+2; i++){
		cin >> s[i];	
	}
	for (int i=2; i<m+2; i++){
		cin >> t[i];
	}
	for (int i=0; i<2; i++){
		for (int j=0; j<m+2; j++){
			dp[i][j] = 2*b;
			dp1[i][j] = dp2[i][j] = dp3[i][j] = -1e8;
		}
	}
	ans = -(a + m*b);
	for (int i=2; i<n+2; i++){
		int x = i%3, y = (i+1)%3;
		for (int j=2; j<m+2; j++){
			dp[x][j] = 2*b;
			dp1[x][j] = dp2[x][j] = dp3[x][j] = -1e8;
			if (s[i] == t[j]){
				dp3[x][j] = v[s[i]] - (j-2)*b + (j+1)*b + (i+1)*b - a;
				if (j==2) dp3[x][j] += a;
				dp3[x][j] = max(dp3[x][j], max(dp3[(i+2)%3][j-1], dp[y][j-2] - 2*a) + v[s[i]] + 2*b);
				dp3[x][j] = max(dp3[x][j], max(dp1[(i+2)%3][j-1], dp2[(i+2)%3][j-1]) + v[s[i]] - a + 2*b);
			}
			dp1[x][j] = max(dp1[x][j-1], dp3[x][j]);
			dp2[x][j] = max(dp2[(i+2)%3][j], dp3[x][j]);
			dp[x][j] = max(dp[x][j],max(dp3[x][j],max(dp[(i+2)%3][j], dp[x][j-1])));
			int tt = dp3[x][j] - (m+2)*b - (i+1)*b - a;
			if (j==m+1) tt += a;
			ans = max(ans, tt);
		}
	}
	cout << ans;
}
