#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int S, N, V, W, K;
vector <pair<int, int>> A[2001];
long long dp[2001], answer;
int main(){
	cin >> S >> N;
	for(int i = 0; i < N; i++){
		cin >> V >> W >> K;
		A[W].push_back(make_pair(V, K));
	}
	for(int i = 1; i <= S; i++){
		sort(A[i].begin(), A[i].end(), greater<pair<int, int>>());
		int index = 0;
		for(int j = 0; j < S / i; j++){
			if(index >= A[i].size()) break;
			for(int k = S; k >= i; k--){
				dp[k] = max(dp[k], dp[k - i] + A[i][index].first);
				answer = max(answer, dp[k]);
			}
			A[i][index].second--;
			if(A[i][index].second == 0) index++;
		}
	}
	cout << answer << endl;
	return 0;
} 
