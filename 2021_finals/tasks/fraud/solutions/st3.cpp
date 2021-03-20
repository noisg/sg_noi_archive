#include <iostream>
#include <vector>
using namespace std;

int N, A[300000], B[300000];
vector<long double> v_left, v_right;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int a = 0; a < N; ++a) cin >> A[a];
    for (int a = 0; a < N; ++a) cin >> B[a];
    bool can = true;
    for (int a = 0; a < N - 1 && can; ++a) {
        if ((A[a] <= A[a + 1]) && (B[a] <= B[a + 1])) can = false;
        else if (((A[a] >= A[a + 1]) && (B[a] > B[a + 1])) ||
                 ((A[a] > A[a + 1]) && (B[a] >= B[a + 1]))) continue;
        else {
            bool is_right = (B[a] - B[a + 1]) > 0;
            long double m = (long double)(A[a + 1] - A[a]) / (long double)(B[a] - B[a + 1]);
            if (is_right) v_right.push_back(m);
            else v_left.push_back(m);
        }
    }
    for (auto l: v_left) {
        for (auto r: v_right) {
            can &= l > r;
            if (!can) break;
        }
        if (!can) break;
    }
    cout << (can ? "YES\n" : "NO\n");
    return 0;
}