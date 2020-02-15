#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=1000000;
long long d[MAXN+1], v[MAXN+1];
long long next_k[MAXN];
int children[MAXN];
int childoff[MAXN+2];
long long ans[MAXN];
int ancestors[MAXN];
int n;
unsigned s;
void dfs(int index, int* ancestors_end){
    if(ancestors_end-ancestors<s)ans[index]=n;
    else ans[index]=*(ancestors_end-s);
    *ancestors_end++=index;
    for(int i=childoff[index];i!=childoff[index+1];++i){
        dfs(children[i], ancestors_end);
    }
    --ancestors_end;
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
        childoff[next_k[next_k[i]]+1]++;
    }
    {
        int childstor=0;
        for(int i=0;i<=n;++i){
            const int tmp=childoff[i];
            childoff[i]=childstor;
            childstor+=tmp;
        }
    }
    for(int i=0;i<n;++i){
        children[childoff[next_k[next_k[i]]+1]++]=i;
    }
    move_backward(childoff,childoff+n+1,childoff+n+2);
    childoff[0]=0;
    for(auto i=childoff[n];i!=childoff[n+1];++i) dfs(children[i], ancestors);
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
