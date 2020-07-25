#include <iostream>
#include <algorithm>
using namespace std;

int N;
int D[300010];
int P[300010];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int a = 0; a < N - 1; ++a) {
        cin >> D[a];
        if (a) D[a] += D[a - 1];
    }
    if (*max_element(D, D + N) - *min_element(D, D + N) != N - 1) { // Note that D[N - 1] = 0
        cout << "-1\n";
        return 0;
    }
    P[0] = N - *max_element(D, D + N);
    for (int a = 1; a < N; ++a) P[a] = P[0] + D[a - 1];
    for (int a = 0; a < N; ++a) cout << P[a] << " \n"[a == N - 1];
    return 0;
}
