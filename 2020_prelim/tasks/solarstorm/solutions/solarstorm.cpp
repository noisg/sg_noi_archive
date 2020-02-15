#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=1000000;
long long d[MAXN+1], v[MAXN+1];
int next_k[MAXN];
vector<int> children[MAXN+1];
int ans[MAXN];
int n;
unsigned s;
void dfs(int index, vector<int>& ancestors){
    if(ancestors.size()<s)ans[index]=n;
    else ans[index]=ancestors[ancestors.size()-s];
    ancestors.push_back(index);
    for(const int x : children[index]){
        dfs(x, ancestors);
    }
    ancestors.pop_back();
}
int main(){
    ios_base::sync_with_stdio(false);
    long long k;
    cin>>n>>s>>k;
    assert(n<=MAXN);
    d[0]=0;
    for(int i=1;i<n;++i){
        int tmp;
        cin>>tmp;
        d[i]=d[i-1]+tmp;
    }
    d[n]=numeric_limits<long long>::max();
    v[0]=0;
    for(int i=0;i<n;++i){
        int tmp;
        cin>>tmp;
        v[i+1]=v[i]+tmp;
    }
    int j=0;
    for(int i=0;i<n;++i){
        while(d[j+1]-d[i]<=k)++j;
        next_k[i]=j;
    }
    for(int i=0;i<n;++i){
        children[next_k[next_k[i]]+1].push_back(i);
    }
    vector<int> ancestors;
    for(const int x : children[n]) dfs(x, ancestors);
    int best_index=0;
    for(int i=1;i<n;++i){
        // change '>' to '>=' and the answer should also be correct
        if(v[ans[i]]-v[i]>v[ans[best_index]]-v[best_index])best_index=i;
    }
    unsigned counter=0;
    for(int tmp=best_index;tmp!=n&&counter!=s;tmp=next_k[next_k[tmp]]+1,++counter);
    cout<<counter<<'\n';
    best_index=next_k[best_index];
    cout<<best_index+1;
    while(--counter>0){
        best_index=next_k[next_k[best_index]+1];
        cout<<' '<<best_index+1;
    }
    cout<<'\n';
}
