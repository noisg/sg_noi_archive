#include <bits/stdc++.h>
using namespace std;
long long H, N;
int main() {
	scanf("%lld%lld", &H, &N);
	long long x;
	scanf("%lld", &x);
	if (x <= 0) puts("-1 -1");
	else {
		long long steps = ((H+(x-1))/x);
		long long d = (steps-1)/N;
		long long p = (steps-1)%N;
		printf("%lld %lld\n", d, p);
	}
}
