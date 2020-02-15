#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=1000000;
long long d[MAXN+1], v[MAXN+1];
long long next_k[MAXN];
long long ans[MAXN];
pair<int,unsigned> parent[MAXN];
int n;
unsigned s;
int dfs(int index, unsigned depth){
    assert(depth>=0);
    if(depth==0)return index;
    if(index==n)return n;
    assert(depth>=parent[index].second);
    const int res=parent[index].second ? dfs(parent[index].first,depth-parent[index].second) : dfs(next_k[next_k[index]]+1,depth-1);
    parent[index]={res,depth};
    return res;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
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
        ans[i]=dfs(i,s);
    }
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
