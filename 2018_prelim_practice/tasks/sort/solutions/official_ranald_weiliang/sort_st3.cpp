#include <bits/stdc++.h>
using namespace std;
int n,a[100005];
int main(){
    scanf("%d",&n);
    for(int x=0;x<n;x++){
        scanf("%d",&a[x]);
    }
    sort(a,a+n);
    for(int x=0;x<n;x++){
        printf("%d\n",a[x]);
    }
    return 0;
}