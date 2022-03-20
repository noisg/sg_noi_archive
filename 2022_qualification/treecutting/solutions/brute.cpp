#include <bits/stdc++.h>
using namespace std;
const int n_max = 3e5+10;
vector<int> adj[n_max];
bitset<n_max> ban;

int deepest(int n, int x) {
    queue<int> q;
    vector<int> ans(n, -1);
    ans[x] = 0;
    int biggest = x;
    q.push(x);
    while(q.size()) {
        int next = q.front();
        q.pop();
        for(int i: adj[next]) {
            if(ans[i] == -1 && !ban[i]) {
                ans[i] = ans[next] + 1;
                if(ans[i] > ans[biggest]) {
                    biggest = i;
                }
                q.push(i);
            }
        }
    }
    x = biggest;
    assert(q.empty());
    ans = vector<int>(n, -1);
    ans[x] = 0;
    biggest = x;
    q.push(x);
    while(q.size()) {
        int next = q.front();
        q.pop();
        for(int i: adj[next]) {
            if(ans[i] == -1 && (!ban[i] || !ban[next])) {
                ans[i] = ans[next] + 1;
                if(ans[i] > ans[biggest]) {
                    biggest = i;
                }
                q.push(i);
            }
        }
    }
    return ans[biggest];
}

int main() {
    int n; cin>>n;
    for(int i=1; i<n; i++) {
        int u,v; cin>>u>>v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 0;
    pair<int,int> a,b;
    for(int i=0; i<n; i++) {
        for(int j: adj[i]) {
            ban[i] = true;
            ban[j] = true;
            if(deepest(n,i) + deepest(n,j)+1 > ans) {
                ans = deepest(n,i) + deepest(n,j)+1;
                a = make_pair(i, j);
                b = make_pair(deepest(n,i), deepest(n,j));
            }
            ans = max(ans, deepest(n,i) + deepest(n,j)+1);
            ban[i] = false;
            ban[j] = false;
        }
    }
    printf("%d\n", ans);
}
