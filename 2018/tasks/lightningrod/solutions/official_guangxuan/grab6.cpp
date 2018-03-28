#include <bits/stdc++.h>
using namespace std;

int x[10000009],y[10000009];

inline int readInt() { 
    int x=0; char ch=getchar_unlocked(); bool s=1; 
    while(ch<'0'||ch>'9'){if(ch=='-')s=0;ch=getchar_unlocked();} 
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar_unlocked();} 
    return s?x:-x; 
} 

int main(){
	int n=readInt();
	for(int i=0;i<n;i++){
		x[i]=readInt(),y[i]=readInt();
	}
	int ans=0;
	for(int i=0;i<n;i++){
		if(y[i]==1)ans++;
		else if((i==0||y[i-1]==0)&&(i==n-1||y[i+1]==0))ans++;
	}
	printf("%d",ans);
}
