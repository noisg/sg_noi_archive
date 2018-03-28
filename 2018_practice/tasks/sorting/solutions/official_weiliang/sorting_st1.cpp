#include "sorting.h"
#include <bits/stdc++.h>
using namespace std;

void sort_questions(int N, int Q, int A[]) {
	if(N == 1) {
		A[0] = 1;
	} else {
		if(compare_difficulty(1, 2)) {
			A[0] = 1;
			A[1] = 2;
		} else {
			A[0] = 2;
			A[1] = 1;
		}
	}
	return;
}
