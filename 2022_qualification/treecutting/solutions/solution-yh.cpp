#include <bits/stdc++.h>
using namespace std;
const int n_max = 3e5+10;
vector<int> adj[n_max];
vector<bool> on_diameter;
int tmp[n_max];

vector<int> longest_path(int n, int x) {
    // for each i=0 to n-1
    // ans[i] gives the distance from x to i
    queue<int> q;
    vector<int> ans(n, -1);
    vector<int> par(n, -1);
    par[x] = -1;
    ans[x] = 0;
    int biggest = x;
    q.push(x);
    while(q.size()) {
        int next = q.front();
        q.pop();
        for(int i: adj[next]) {
            if(ans[i] == -1) {
                ans[i] = ans[next] + 1;
                par[i] = next;
                if(ans[i] > ans[biggest]) {
                    biggest = i;
                }
                q.push(i);
            }
        }
    }
    vector<int> ans2;
    ans2.push_back(biggest);
    while(biggest != -1) {
        biggest = par[biggest];
        ans2.push_back(biggest);
    }
    return ans2;
}

int longest_path2(int n, int x) { // avoid vertex y
    // for each i=0 to n-1
    // ans[i] gives the distance from x to i
    queue<int> q;
    tmp[x] = 0;
    int biggest = x;
    q.push(x);
    while(q.size()) {
        int next = q.front();
        q.pop();
        for(int i: adj[next]) {
            if(tmp[i] == -1 && !on_diameter[i]) {
                tmp[i] = tmp[next] + 1;
                if(tmp[i] > tmp[biggest]) {
                    biggest = i;
                }
                q.push(i);
            }
        }
    }
    return biggest;
}

int deepest(int x, int y) {
    // x is parent, deepest path in direction of y
    int ans = 1;
    for(int j: adj[y]) {
        if(j != x) {
            ans = max(ans, 1 + deepest(y, j));
        }
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i=1; i<n; i++) {
        int u,v;
        scanf("%d%d", &u, &v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> diameter = longest_path(n, longest_path(n, 0).front());
    diameter.pop_back();
    on_diameter = vector<bool>(n, false);
    for(int i: diameter) {
        on_diameter[i] = true;
    }
    vector<int> deep(diameter.size(), 0);
    for(int i=0; i<diameter.size(); i++) {
        for(int j: adj[diameter[i]]) {
            if(!on_diameter[j]) {
                deep[i] = max(deep[i], deepest(diameter[i], j));
            }
        }
    }
    int d = diameter.size();
    if(d==n-1) {
        printf("%d\n", n-1);
        return 0;
    }
    vector<int> pref(d, 0);
    pref[0] = 0;
    for(int i=1; i<d; i++) {
        pref[i] = max(pref[i], i + deep[i]);
    }

    vector<int> suff(d, 0);
    suff[d-1] = 0;
    for(int i=d-2; i>=0; i--) {
        suff[i] = max(suff[i+1], d-1-i+deep[i]);
    }
    int ans = 0;

    for(int i=0; i+1<d; i++) {
        ans = max(ans, pref[i] + suff[i+1]+1);
    }
    vector<int> far;
    for(int i=0; i<n; i++) {
        tmp[i] = -1;
    }
    for(int i: diameter) {
        //printf("d: %d\n", i);
        for(int j: adj[i]) {
            if(!on_diameter[j]) {
                far.push_back(longest_path2(n, j));
            }
        }
    }
    for(int i=0; i<n; i++) {
        tmp[i] = -1;
    }
    for(int i: far) {
        ans = max(ans, d + tmp[longest_path2(n, i)]);
    }
    printf("%d\n", ans);
}
