#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
#define MAX_HEIGHT 5000
using namespace std;
int back_arr[2][MAX_HEIGHT+1];
multiset<int>::iterator its[MAX_HEIGHT+1];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,h;
    cin>>n>>h;
    int* arrprev=back_arr[0];
    int* arrcurr=back_arr[1];
    {
        int x;
        cin>>x;
        for(int j=0;j<=MAX_HEIGHT;++j){
            arrprev[j]=abs(j-x);
        }
    }
    for(int i=1;i<n;++i){
        int x;
        cin>>x;
        multiset<int> st;
        for(int j=0;j<min(MAX_HEIGHT,h);++j)its[j]=st.emplace(arrprev[j]);
        for(int j=0;j<=MAX_HEIGHT;++j){
            if(j+h<=MAX_HEIGHT)its[j+h]=st.emplace(arrprev[j+h]);
            arrcurr[j]=*st.begin();
            arrcurr[j]+=abs(j-x);
            if(j-h>=0)st.erase(its[j-h]);
        }
        swap(arrprev,arrcurr);
    }
    cout<<*min_element(arrprev,arrprev+MAX_HEIGHT+1)<<endl;
}
