#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef pair<long long, int> elem;
typedef tree<elem,null_type,std::less<elem>,rb_tree_tag,tree_order_statistics_node_update> stat_tree;
constexpr int MAXN=300'000;
long long arr[MAXN];
int lefts[MAXN];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    assert(3<=n&&n<=MAXN);
    stat_tree st;
    long long ans=0;
    for(int i=0;i<n;++i){
        cin>>arr[i];
        assert(0<=arr[i]&&arr[i]<=1'000'000'000'000'000'000ll);
        lefts[i]=st.order_of_key(make_pair(arr[i],0));
        st.insert(make_pair(arr[i],i));
    }
    st.clear();
    for(int i=n-1;i>=0;--i){
        const int ct=st.order_of_key(make_pair(arr[i],0));
        ans+=static_cast<long long>(ct)*lefts[i];
        st.insert(make_pair(arr[i],i));
    }
    cout<<ans<<'\n';
}
