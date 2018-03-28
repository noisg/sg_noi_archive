#include <bits/stdc++.h>
using namespace std;
int n,a[100005];
int main(){
    scanf("%d",&n);
    for(int x=0;x<n;x++){
        scanf("%d",&a[x]);
    }
    for(int x=0;x<n;x++){
        for(int y=0;y<n-1;y++){
            if(a[y]>a[y+1]) swap(a[y],a[y+1]);
        }
    }
    for(int x=0;x<n;x++){
        printf("%d\n",a[x]);
    }
    return 0;
}