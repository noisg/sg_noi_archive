#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
priority_queue<long long,vector<long long>,less<long long>> lefts;
priority_queue<long long,vector<long long>,greater<long long>> rights;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,h;
    cin>>n>>h;
    {
        int x;
        cin>>x;
        lefts.push(x);
        rights.push(x);
    }
    long long minval=0;
    for(int i=1;i<n;++i){
        int x;
        cin>>x;
        long long shift=static_cast<long long>(i)*h;
        long long leftborderval=lefts.top()-shift;
        long long rightborderval=rights.top()+shift;
        if(x<leftborderval){
            lefts.push(x+shift);
            lefts.push(x+shift);
            lefts.pop();
            rights.push(leftborderval-shift);
            minval+=abs(leftborderval-x);
        }
        else if(x>rightborderval){
            rights.push(x-shift);
            rights.push(x-shift);
            rights.pop();
            lefts.push(rightborderval+shift);
            minval+=abs(rightborderval-x);
        }
        else{
            lefts.push(x+shift);
            rights.push(x-shift);
        }
    }
    cout<<minval<<endl;
}
