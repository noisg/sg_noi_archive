#include "sorting.h"
#include <bits/stdc++.h>
using namespace std;

void sort_questions(int N, int Q, int A[]) {
	for (int i = 1; i <= N; ++i) A[i-1] = i;
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < N - i - 1; j++) {
			if(!compare_difficulty(A[j], A[j + 1])) {
				swap(A[j], A[j + 1]);
			}
		}
	}
	return;
}
