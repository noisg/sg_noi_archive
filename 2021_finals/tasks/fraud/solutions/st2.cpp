#include <iostream>
using namespace std;

int N, A[300000], B[300000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int a = 0; a < N; ++a) cin >> A[a];
    for (int a = 0; a < N; ++a) cin >> B[a];
    bool can = (A[0] - A[1] > 0) + (B[0] - B[1] > 0);
    cout << (can ? "YES\n" : "NO\n");
    return 0;
}