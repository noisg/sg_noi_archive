#include <bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
    scanf("%d",&n);
    scanf("%d %d",&a,&b);
    if(a<=b) printf("%d\n%d\n",a,b);
    else printf("%d\n%d\n",b,a);
    return 0;
}