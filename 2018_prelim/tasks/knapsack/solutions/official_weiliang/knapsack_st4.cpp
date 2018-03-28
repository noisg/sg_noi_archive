#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N, S, M;
ll W[2000000], V[2000000], dp[2005];
int main() {
  scanf("%d%d", &S, &N);
    M = 0;
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
      ll v, w, cnt;
      scanf("%lld%lld%lld", &v, &w, &cnt);
      cnt = min(cnt, S/w);
      for (int k = 0; cnt > 0; ++k) {
        if ((1<<k) >= cnt) {
          V[M] = v*cnt;
          W[M] = w*cnt;
          if (W[M] <= S) ++M;
          ++M;
          cnt = 0;
        } else {
          V[M] = v*(1<<k);
          W[M] = w*(1<<k);
          if (W[M] <= S) ++M;
          else break;
          ++M;
          cnt -= (1<<k);
        }
      }
    }
    memset(dp, 0, sizeof dp);
    for (int x = 0; x < M; ++x) {
      for (ll s = S; s >= W[x]; --s) {
        dp[s] = max(dp[s], dp[s-W[x]]+V[x]);
      }
    }
    printf("%lld\n", *max_element(dp, dp+S+1)+ans);
}
