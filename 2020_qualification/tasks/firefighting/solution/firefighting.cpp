#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'000;
vector<pair<int, int>> adjlist[MAXN];
long long k;
vector<int> ans;
pair<bool, long long> dfs(int index, int prev,long long dist) {
    long long max_overflow=numeric_limits<long long>::min();
    long long max_underflow=0;
    for(const pair<int,int>& pr : adjlist[index]) {
        if(pr.first!=prev){
            pair<bool, long long> res=dfs(pr.first,index,pr.second);
            if(res.first){
                max_overflow=max(max_overflow,res.second);
            }
            else {
                max_underflow=max(max_underflow,res.second);
            }
        }
    }
    pair<bool, long long> ret;
    if(max_overflow>=max_underflow){
        ret={true,max_overflow-dist};
    }
    else {
        ret={false,max_underflow+dist};
    }
    if(!ret.first&&ret.second>k){
        ans.push_back(index);
        ret={true,k-dist};
    }
    if(ret.first&&ret.second<0){
        ret={false,0};
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin>>n>>k;
    for(int i=1;i<n;++i){
        int a,b,w;
        cin>>a>>b>>w;
        --a;--b;
        adjlist[a].emplace_back(b,w);
        adjlist[b].emplace_back(a,w);
    }
    dfs(0,-1,numeric_limits<long long>::max()>>2);
    cout<<ans.size()<<'\n';
    auto it=ans.begin();
    cout<<(*it+1);
    for(++it;it!=ans.end();++it){
        cout<<' '<<(*it+1);
    }
    cout<<'\n';
}
