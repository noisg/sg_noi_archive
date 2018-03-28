#include "sorting.h"
#include <bits/stdc++.h>
using namespace std;

static int N, Q, D[100005], calls = 0;

bool compare_difficulty(int X, int Y){
	if (X <= 0 || X > N || Y <= 0 || Y > N) {
		fprintf(stderr, "Wrong Answer: compare_difficulty() parameter out of range.\n");
		exit(1);
	}
	if(++calls > Q) {
		fprintf(stderr, "Wrong Answer: compare_difficulty() called too many times.\n");
		exit(1);
	}
	return D[X - 1] < D[Y - 1];
}

int main() {
	if (scanf("%d %d", &N, &Q) != 2) {
		fprintf(stderr, "Invalid Input Format\n");
		exit(1);
	}
	for (int i = 0; i < N; i++) {
		if (scanf("%d", &D[i]) != 1) {
			fprintf(stderr, "Invalid Input Format\n");
			exit(1);
		}
	}
	int A[N];
	memset(A, 0, sizeof(A));
	sort_questions(N, Q, A);
	fprintf(stderr, "You made %d call(s) to compare_difficulty().\n", calls);
	for(int i = 0; i < N; i++) {
		printf("%d\n", A[i]);
	}
	return 0;
}
