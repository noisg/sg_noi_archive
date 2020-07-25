#include <bits/stdc++.h>
using namespace std;
int arr[300'000];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    int xmin=0,xmax=0,xcurr=0;
    for(int i=1;i<n;++i){
        int tmp;
        cin>>tmp;
        xcurr+=tmp;
        arr[i]=xcurr;
        xmin=min(xmin,xcurr);
        xmax=max(xmax,xcurr);
    }
    if(xmax-xmin+1<n){
        cout<<"-1\n";
    }
    else {
        const int offset=1-xmin;
        for(int i=0;i<n;++i){
            cout<<arr[i]+offset<<' ';
        }
        cout<<'\n';
    }
}
