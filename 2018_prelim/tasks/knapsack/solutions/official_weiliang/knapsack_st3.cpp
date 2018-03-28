// 0-1 Knapsack (IV)
// should be MLE/TLE (too slow?)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MAX_N 110 // actually 100
#define MAX_NK 1010 // actually 100*100 = 10000
#define MAX_S 10010 // actually 10000

int i, j, S, N, K, new_N;
ll V, W, new_V[MAX_NK], new_W[MAX_NK]; // transformed data set, can exceed the value of 32 bit signed integer!
ll memo[MAX_NK][MAX_S]; // 80 MB * 4 = 320 MB... > 256 MB

ll value(int id, int w) {
  if (id == new_N || w == 0) return 0;
  if (memo[id][w] != -1) return memo[id][w];
  if (new_W[id] > w) return memo[id][w] = value(id+1, w);
  return memo[id][w] = max(value(id+1, w), new_V[id] + value(id+1, w-new_W[id]));
}

int main() {
  // freopen("in.txt", "r", stdin);
    scanf("%d %d", &S, &N);
    // assert(1 <= S && S <= 10000);
    // assert(1 <= N && N <= 100);
    for (i = new_N = 0; i < N; i++) {
      scanf("%lld %lld %d", &V, &W, &K);
      // assert(0 <= V && V <= 100000000);
      // assert(0 <= W && W <= 2000);
      // assert(1 <= K && K <= 100);
      for (j = 1; j <= K; j++) new_V[new_N] = V, new_W[new_N++] = W; // linear growth, multiple copies of the same thing
    }
    // printf("NEWN = %d\n", new_N);
    memset(memo, -1, sizeof memo);
    printf("%lld\n", value(0, S));
  return 0;
}
