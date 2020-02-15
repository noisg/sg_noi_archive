#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
#define ll long long

ll A[N], prefix[N];
int V[N];
int nxt[N], before[N], parent[N];
vector<int> adj[N];

int n, s, ans_start;
ll ans = 0;

vector<int> LOL;

void dfs(int u) {
  LOL.push_back(u);
  if(u != n) {
    int l = before[u];
    int r = nxt[LOL[max(0, (int)LOL.size() - s)]] - 1;
    ll candidate = prefix[r] - (l == -1 ? 0 : prefix[l]);
    //cout<<"DBG --> "<<u<<" : "<<l<<" "<<r<<" : "<<candidate<<endl;
    if(candidate > ans) {
      ans = candidate;
      ans_start = u;
    }
  }
  for(auto v : adj[u]) {
    dfs(v);
  }
  LOL.pop_back();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int diff;
  ll k;
  cin>>n>>s>>k;
  A[0] = 0;
  for(int i = 1; i < n; i++) {
    cin>>diff;
    A[i] = A[i - 1] + diff;
  }
  for(int i = 0; i < n; i++) {
    cin>>V[i];
    prefix[i] = (i == 0 ? 0 : prefix[i - 1]) + V[i];
  }
  prefix[n] = prefix[n - 1];
  A[n] = A[n - 1] + 2*k;
  int current_ptr = 0;
  nxt[n] = n;
  for(int i = 0; i < n; i++) {
    for(int j = current_ptr; j <= n; j++) {
      if(A[j] - A[i] > k) {
        current_ptr = j;
        nxt[i] = j;
        break;
      }
    }
  }
  current_ptr = n;
  for(int i = n; i >= 0; i--) {
    for(int j = current_ptr; j >= -1; j--) {
      if(j == -1 or A[i] - A[j] > k) {
        current_ptr = j;
        before[i] = j;
        break;
      }
    }
  }
//  for(int i = 0; i < n; i++) cout<<i<<" Before: "<<before[i]<<", Next: "<<nxt[i]<<endl;
  for(int i = 0; i < n; i++) {
    int jump_to = nxt[i];
    if(jump_to != n) {
      jump_to = nxt[jump_to] - 1;
    }
    //cout<<i<<" --> "<<jump_to<<endl;
    adj[jump_to].push_back(i);
    parent[i] = jump_to;
  }
  dfs(n);
  vector<int> Q;
  for(int i = 0; i < s; i++) {
    Q.push_back(ans_start);
    ans_start = parent[ans_start];
    if(ans_start == n)  break;
  }
  cout<<Q.size()<<endl;
  for(auto v : Q) cout<<v + 1<<" ";
  cout<<endl;
}
