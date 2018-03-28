#include <bits/stdc++.h>
using namespace std;
long long H, N;
int main() {
	scanf("%lld%lld", &H, &N);
	long long x;
	scanf("%lld", &x);
	if (x <= 0) puts("-1 -1");
	else printf("%lld %lld\n", ((H+(x-1))/x)-1, 0ll);
}
