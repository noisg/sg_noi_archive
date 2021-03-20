#include <iostream>
using namespace std;

int N, A[300000], B[300000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int a = 0; a < N; ++a) cin >> A[a];
    for (int a = 0; a < N; ++a) cin >> B[a];
    long double m_left = 1e9, m_right = 0;
    bool can = true;
    for (int a = 0; a < N - 1 && can; ++a) {
        if ((A[a] <= A[a + 1]) && (B[a] <= B[a + 1])) can = false;
        else if (((A[a] >= A[a + 1]) && (B[a] > B[a + 1])) ||
                 ((A[a] > A[a + 1]) && (B[a] >= B[a + 1]))) continue;
        else {
            bool right = (B[a] - B[a + 1]) > 0;
            long double m = (long double)(A[a + 1] - A[a]) / (long double)(B[a] - B[a + 1]);
            if (right) m_right = max(m_right, m);
            else m_left = min(m_left, m);
        }
    }
    can &= m_left > m_right;
    cout << (can ? "YES\n" : "NO\n");
    return 0;
}