#include <bits/stdc++.h>
using namespace std;
inline int readInt() {
    int x = 0;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') ch = getchar_unlocked();
    while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar_unlocked();
	}
    return x;
}

int X[10000000], Y[10000000];

int main(){
	int N = readInt();
	for(int i = 0; i < N; i++) {
		X[i] = readInt();
		Y[i] = readInt();
		// write code here
	}
	// write code here
	return 0;
}
