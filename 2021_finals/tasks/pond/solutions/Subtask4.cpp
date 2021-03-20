#include <bits/stdc++.h>
using namespace std;

int main() {
    long long N, K, t = 0, i, j;
    scanf("%lld %lld", &N, &K);
    --K;
    printf("%lld", K * (K + 1) / 2 + (N - K) * (N - K - 1) / 2 + 2 * K * (N - K - 1));
    return 0;
}
