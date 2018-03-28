#include "sorting.h"
#include <bits/stdc++.h>
using namespace std;

bool cmp(int a, int b){
    return compare_difficulty(a, b);
}
void sort_questions(int N, int Q, int A[]) {
	if(N == 2) {
		if(compare_difficulty(1, 2)) {
			A[0] = 1;
			A[1] = 2;
		} else {
			A[0] = 2;
			A[1] = 1;
		}
		return;
	}
	for (int i = 0; i < N; i++) A[i] = i + 1;
	sort(A, A + N, cmp);
	return;
}
