#include <bits/stdc++.h> 
using namespace std; 
stack<pair<int,int> >s; 
inline int readInt() {
    int x=0; char ch=getchar_unlocked(); bool s=1;
    while(ch<'0'||ch>'9'){if(ch=='-')s=0;ch=getchar_unlocked();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar_unlocked();}
    return s?x:-x;
}

int main(){ 
    int n = readInt(); 
    for(int i=0;i<n;i++){
        int x = readInt();
        int y = readInt();
        bool add=1; 
        while(s.size()){ 
            int tx=s.top().first,ty=s.top().second; 
            if(x-tx<=ty-y){add=0;break;} 
            if(x-tx<=y-ty)s.pop(); 
            else break; 
        } 
        if(add)s.push(make_pair(x,y)); 
    } 
    printf("%d",(int)s.size()); 
} 