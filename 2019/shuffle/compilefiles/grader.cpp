#include <bits/stdc++.h>
#include "shuffle.h"
using namespace std;

static int N, B, K, Q, ST, order[1005], q;
static mt19937 mt;

int myrandom(int i){return mt()%i;}

vector< vector<int> > shuffle(vector< vector<int> > packed_cards) {
	q++;
	if (q > Q) {
		printf("Wrong Answer. Used too many queries.\n");
		exit(0);
	}
	vector<int> card_list;
	if (packed_cards.size() != B) {
		printf("Wrong Answer. Number of packs is incorrect.\n");
		exit(0);
	}
	for (int i = 0; i < packed_cards.size(); i++) {
		if (packed_cards[i].size() != K) {
			printf("Wrong Answer. Number of cards in each pack is incorrect.\n");
			exit(0);
		}
	}
	for (int i = 0; i < packed_cards.size(); i++) {
		for (int j = 0; j < packed_cards[i].size(); j++) {
			card_list.push_back(packed_cards[i][j]);
		}
	}
	if (card_list.size() != N) {
		printf("Wrong Answer. Query parameter not of length %d.\n", N);
		exit(0);
	}
	vector<int> sorted_card_list = card_list;
	sort(sorted_card_list.begin(), sorted_card_list.end());
	for (int i = 0; i < N; i++) {
		if (sorted_card_list[i] != i + 1) {
			printf("Wrong Answer. Query parameter not a permutation.\n");
			exit(0);
		}
	}
	for (int i = 0; i < B; i++) random_shuffle(packed_cards[i].begin(), packed_cards[i].end(), myrandom);
	if (ST != 3) random_shuffle(packed_cards.begin(), packed_cards.end(), myrandom);
	vector< vector<int> > res;
	for (int i = 0; i < B; i++) {
		vector<int> pack;
		for (int j = 0; j < K; j++) {
			pack.push_back(order[packed_cards[i][j]]);
		}
		res.push_back(pack);
	}
	return res;
}

int main() {
	if (scanf("%d%d%d%d%d", &N, &B, &K, &Q, &ST) != 5) {
		printf("Internal grader error.\n");
		return 0;
	}
	mt = mt19937(1864);
	for (int i = 1; i <= N; i++) {
		if (scanf("%d", &order[i]) != 1) {
			printf("Internal grader error.\n");
			return 0;
		}
	}
	char secret_key[50];
	int at = scanf(" %s", secret_key);
	vector<int> res = solve(N, B, K, Q, ST);
	if (res.size() != N) {
		printf("Wrong Answer. Returned result not of length %d.\n", N);
		return 0;
	}
	for (int i = 0; i < N; i++) {
		if (order[i+1] != res[i]) {
			printf("Wrong Answer.\n");
			return 0;
		}
	}
	printf("Correct. Used %d out of %d queries.\n", q, Q);
	printf("%s\n", secret_key);
}
