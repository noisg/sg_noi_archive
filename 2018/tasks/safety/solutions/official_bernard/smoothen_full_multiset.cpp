#include <iostream>
#include <algorithm>
#include <set>
#include <functional>
using namespace std;
multiset<long long,greater<long long>> lefts;
multiset<long long,less<long long>> rights;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,h;
    cin>>n>>h;
    {
        int x;
        cin>>x;
        lefts.insert(x);
        rights.insert(x);
    }
    long long minval=0;
    for(int i=1;i<n;++i){
        int x;
        cin>>x;
        long long shift=static_cast<long long>(i)*h;
        auto leftborder=lefts.begin();
        long long leftborderval=*leftborder-shift;
        auto rightborder=rights.begin();
        long long rightborderval=*rightborder+shift;
        if(x<leftborderval){
            auto hint=lefts.insert(x+shift);
            lefts.insert(hint,x+shift);
            lefts.erase(leftborder);
            rights.insert(rightborder,leftborderval-shift);
            minval+=abs(leftborderval-x);
        }
        else if(x>rightborderval){
            auto hint=rights.insert(x-shift);
            rights.insert(hint,x-shift);
            rights.erase(rightborder);
            lefts.insert(leftborder,rightborderval+shift);
            minval+=abs(rightborderval-x);
        }
        else{
            lefts.insert(leftborder,x+shift);
            rights.insert(rightborder,x-shift);
        }
    }
    cout<<minval<<endl;
}
