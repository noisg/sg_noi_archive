#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
#define MAX_HEIGHT 400
using namespace std;
int back_arr[2][MAX_HEIGHT+1];
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
        for(int j=0;j<=MAX_HEIGHT;++j){
            arrcurr[j]=*min_element(arrprev+max(j-h,0),arrprev+min(j+h+1,MAX_HEIGHT+1));
            arrcurr[j]+=abs(j-x);
        }
        swap(arrprev,arrcurr);
    }
    cout<<*min_element(arrprev,arrprev+MAX_HEIGHT+1)<<endl;
}
