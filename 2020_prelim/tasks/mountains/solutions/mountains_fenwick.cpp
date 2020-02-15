#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=300'000;
int n;
struct {
    int data_[MAXN+1];
    int query(int index){
        int ret=0;
        for(;index>0;index-=(index&-index)){
            ret+=data_[index];
        }
        return ret;
    }
    void update(int index){
        for(++index;index<=n;index+=(index&-index)){
            ++data_[index];
        }
    }
} fw;
pair<long long, int> arr[MAXN];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    assert(3<=n&&n<=MAXN);
    for(int i=0;i<n;++i){
        cin>>arr[i].first;
        assert(0<=arr[i].first&&arr[i].first<=1'000'000'000'000'000'000ll);
        arr[i].second=i;
    }
    sort(arr,arr+n,[](const pair<long long, int>& a, const pair<long long, int>& b){
        return a.first<b.first;
    });
    long long ans=0;
    for(int i=0;i<n;){
        const long long val=arr[i].first;
        int j;
        for(j=i;j<n&&arr[j].first==val;++j){
            const int idx=arr[j].second;
            const int tmp=fw.query(idx);
            ans+=tmp*static_cast<long long>(i-tmp);
        }
        for(;i<j;++i){
            const int idx=arr[i].second;
            fw.update(idx);
        }
    }
    cout<<ans<<'\n';
}
