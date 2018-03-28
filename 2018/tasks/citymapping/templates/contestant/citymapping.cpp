#include "citymapping.h"

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	for (int i = 0; i < N - 1; i++) {
		A[i] = 1;
		B[i] = 2;
		W[i] = 1;
	}
	return;
}
