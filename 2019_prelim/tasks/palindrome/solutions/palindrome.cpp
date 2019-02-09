#include <bits/stdc++.h>
using namespace std;

long long S, E;

bool is_palindrome(long long x) {
	vector<int> v;
	while (x > 0) {
		v.push_back(x%10);
		x /= 10;
	}
	for (int i = 0; i < v.size(); i++) if (v[i] != v[v.size() - i - 1]) return false;
	return true;
}

int main() {
	scanf("%lld%lld", &S, &E);
	for (long long i = S; i <= E; i++) {
		if (is_palindrome(i)) printf("Palindrome!\n");
		else printf("%lld\n", i);
	}
}
