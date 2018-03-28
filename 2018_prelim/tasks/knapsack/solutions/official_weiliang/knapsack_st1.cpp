#include <bits/stdc++.h>
using namespace std;
long long s,n,w,v,k;
int main(){
	scanf("%lld %lld",&s,&n);
	scanf("%lld %lld %lld",&v,&w,&k);
	printf("%lld\n",v*min(k,s/w));
	return 0;
}

