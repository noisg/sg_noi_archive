#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
	FILE *in = fopen(argv[1], "r");
	FILE *uout = fopen(argv[3], "r");
	int T, N, Q, x;
	fscanf(in, "%d%d%d", &T, &N, &Q);
	for (int i = 0; i < T*4; i++) {
		fscanf(in, "%d", &x);
	}
	char secret_key[50], found_key[50];
	memset(secret_key, 0, sizeof(secret_key));
	memset(found_key, 0, sizeof(found_key));
	fscanf(in, " %s", &secret_key);
	if (Q != 50) {
		int q, QQ;
		if (fscanf(uout, "Correct. Used %d out of %d queries.\n", &q, &QQ) != 2) {
			printf("0\n");
			fprintf(stderr, "Output isn't correct\n");
			return 0;
		} else {
			if (QQ != Q) {
				printf("0\n");
				fprintf(stderr, "Internal grader error.\n");
				return 0;
			} else {
				fscanf(uout, " %s", &found_key);
				if (strcmp(found_key, secret_key)) {
					printf("0\n");
					fprintf(stderr, "Internal grader error.\n");
					return 0;
				} else {
					printf("1\n");
					fprintf(stderr, "Output is correct\n");
					return 0;
				}
			}
		}
	} else {
		int q, QQ;
		if (fscanf(uout, "Correct. Used %d out of %d queries.\n", &q, &QQ) != 2) {
			printf("0\n");
			fprintf(stderr, "Output isn't correct\n");
			return 0;
		} else {
			if (QQ != Q) {
				printf("0\n");
				fprintf(stderr, "Internal grader error.\n");
				return 0;
			} else {
				fscanf(uout, " %s", &found_key);
				if (strcmp(found_key, secret_key)) {
					printf("0\n");
					fprintf(stderr, "Internal grader error.\n");
					return 0;
				} else {
					if (q > 33) {
						printf("%lf\n", (40.0 - 30.0 * (double)(q - 34) / 17) / 49);
					} else printf("1\n");
					fprintf(stderr, "Output is correct\n");
					return 0;
				}
			}
		}
	}
}
