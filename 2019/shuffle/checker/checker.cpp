#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
	FILE *in = fopen(argv[1], "r");
	FILE *uout = fopen(argv[3], "r");
	int N, B, K, Q, ST, q, QQ;
	fscanf(in, "%d%d%d%d%d", &N, &B, &K, &Q, &ST);
	for (int i = 0; i < N; i++) {
		int x;
		fscanf(in, "%d", &x);
	}
	char secret_key[50], u_secret_key[50];
	fscanf(in, " %s", &secret_key);
	if (fscanf(uout, "Correct. Used %d out of %d queries.\n", &q, &QQ) != 2) {
		printf("0\nOutput isn't correct\n");
		return 0;
	}
	fscanf(uout, " %s", &u_secret_key);
	if (QQ != Q) {
		printf("0\nInternal grader error.\n");
		return 0;
	}
	if (strcmp(secret_key, u_secret_key)) {
		printf("0\nInternal grader error.\n");
		return 0;
	}
	if (ST != 6) {
		printf("100\nOutput is correct\n");
	} else {
		if (q > 500) printf("%lf\nOutput is correct\n", 8.0/52*100);
		else if (q > 50) printf("%lf\nOutput is correct\n", 17.0/52*100);
		else if (q > 9) printf("%lf\nOutput is correct\n", (22.0+30.0*((50.0-q)/41.0)*((50.0-q)/41.0))/52*100);
		else printf("100\nOutput is correct\n");
	}
}
