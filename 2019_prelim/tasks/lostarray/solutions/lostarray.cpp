#include <bits/stdc++.h>
using namespace std;
 
 
int smallest[100005], largest[100005], N, M;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    cin >> N >> M;
 
    for(int i=0; i<M; i++) {
        int A, B, C; cin >> A >> B >> C;
        smallest[A] = max(smallest[A], C);
        smallest[B] = max(smallest[B], C);
    }
 
    for(int i=0; i<N; i++) smallest[i+1] = max(smallest[i+1], 1);
 
    for(int i=1; i<=N; i++) cout << smallest[i] << ' ';
}
