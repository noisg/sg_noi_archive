#include <bits/stdc++.h>
using namespace std;

int N, Q, S;
vector< pair< pair<int, int>, int > > edgelist;

int main(int argc, char *argv[]) {
	double score;
	char lang[1005];
	FILE *inf = fopen(argv[1], "r");
	fscanf(inf, "%d%d%d", &N, &Q, &S);
	for (int i = 0; i < N - 1; i++) {
		int a, b, w;
		fscanf(inf, "%d%d%d", &a, &b, &w);
		edgelist.push_back(make_pair(make_pair(min(a, b), max(a, b)), w));
	}
	sort(edgelist.begin(), edgelist.end());
	// FILE *uout = fopen(argv[3], "r");
	freopen(argv[3], "r", stdin);
	if (scanf("Score: %lf%%\n", &score) == 1) {
		string str;
		getline(cin, str);
		for (int i = 0; i < N - 1; i++) {
			int a, b, w;
			if (scanf("%d%d%d", &a, &b, &w) != 3 || a != edgelist[i].first.first || b != edgelist[i].first.second || w != edgelist[i].second) {
				printf("0\n");
				fprintf(stderr, "Invalid Submission\n");
				exit(0);
			}
		}
		printf("%.4lf\n", score/100);
		fprintf(stderr, "%s\n", str.c_str());
	}
	else if (scanf("Language not supported: %s\n", lang) == 1) {
		printf("0\n");
		fprintf(stderr, "Language not supported: %s\n", lang);
	} else {
		printf("0\n");
		fprintf(stderr, "Invalid Submission\n");
	}
}
