#include <iostream>
using namespace std;
int cnt[200001], N, M, u;
int main(){
	cin >> N >> M;
	for(int i = 0; i < 2 * (N + M - 1); i++){
		cin >> u;
		if(cnt[u] > 0) cout << cnt[u] << " 1" << endl;
		cnt[u]++;
	}
	return 0;
}
