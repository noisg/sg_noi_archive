#include <iostream>
using namespace std;

int N, A[300000], B[300000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int a = 0; a < N; ++a) cin >> A[a];
    for (int a = 0; a < N; ++a) cin >> B[a];
    bool can = true;
    for (int a = 0; a < N - 1; ++a)
        can &= A[a] > A[a + 1];
    cout << (can ? "YES\n" : "NO\n");
    return 0;
}