#include <iostream>
#include <algorithm>
using namespace std;
constexpr unsigned MAX_VAL = 500000001;
int main(){
    ios_base::sync_with_stdio(false);
    unsigned n,m,h;
    cin>>n>>m>>h;
    unsigned*arr=new unsigned[n*m];
    fill_n(arr,n*m,0);
    arr[0]=1;
    for(unsigned i=0;i<n-1;++i){
        for(unsigned j=0;j<h;++j){
            unsigned c,q;
            cin>>c>>q;
            if(c>i){
                for(unsigned k=q;k<m;++k){
                    for(unsigned l=0;l<=k-q;++l){
                        arr[c*m+k]=min(MAX_VAL,arr[c*m+k]+arr[i*m+l]);
                    }
                }
            }
        }
    }
    for(unsigned i=0;i<m;++i){
        if(i>0)cout<<' ';
        cout<<arr[(n-1)*m+i];
    }
    cout<<'\n';
    delete[] arr;
}
