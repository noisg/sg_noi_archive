#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int A[N], B[N];

pair<int, pair<int, int> > C[N];

int main() {
  cin.tie(NULL);
  ios::sync_with_stdio(false);
  int n, a, b;
  cin>>n>>a>>b;
  for(int i = 0; i < n; i++) {
    cin>>A[i];
  }
  for(int i = 0; i < n; i++) {
    cin>>B[i];
  }
  for(int i = 0; i < n; i++) {
    C[i] = make_pair(B[i] - A[i], make_pair(A[i], B[i]));
  }
  sort(C, C + n);
  int ans = 0;
  for(int i = 0; i < a; i++)  ans += C[i].second.first;
  for(int i = a; i < n; i++)  ans += C[i].second.second;
  cout<<ans<<endl;
}

