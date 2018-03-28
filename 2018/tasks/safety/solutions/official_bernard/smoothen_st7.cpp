#include <iostream>
#include <utility>
#include <algorithm>
#include <deque>
#define MAX_HEIGHT 5000
using namespace std;
int back_arr[2][MAX_HEIGHT+1];
inline void consider_insert(deque<pair<int,int>>& dq, int index, int value){
    while(!dq.empty()&&dq.back().second>=value)dq.pop_back();
    dq.emplace_back(index,value);
}
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
        deque<pair<int,int>> dq; // index, value
        for(int j=0;j<min(MAX_HEIGHT,h);++j){
            consider_insert(dq,j,arrprev[j]);
        }
        for(int j=0;j<=MAX_HEIGHT;++j){
            if(j+h<=MAX_HEIGHT)consider_insert(dq,j+h,arrprev[j+h]);
            arrcurr[j]=dq.front().second;
            arrcurr[j]+=abs(j-x);
            if(dq.front().first==j-h)dq.pop_front();
        }
        swap(arrprev,arrcurr);
    }
    cout<<*min_element(arrprev,arrprev+MAX_HEIGHT+1)<<endl;
}
