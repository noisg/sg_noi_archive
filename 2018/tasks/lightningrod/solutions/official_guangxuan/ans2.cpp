#include <bits/stdc++.h>
using namespace std;

inline int readInt() { 
    int x=0; char ch=getchar_unlocked(); bool s=1; 
    while(ch<'0'||ch>'9'){if(ch=='-')s=0;ch=getchar_unlocked();} 
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar_unlocked();} 
    return s?x:-x; 
} 

int pref[10000009],suff[10000009];

int main(){
	int n=readInt();
	for(int i=0;i<n;i++){
		int x=readInt(),y=readInt();
		pref[i]=x+y;
		suff[i]=y-x;
		if(i)pref[i]=max(pref[i],pref[i-1]);
	}
	int ans=0;
	for(int i=n-1;i>=0;i--){
		ans+=((i==0)||pref[i]>pref[i-1])&&((i==n-1)||suff[i]>suff[i+1]);
		if(i!=n-1)suff[i]=max(suff[i],suff[i+1]);
	}
	printf("%d",ans);
}
