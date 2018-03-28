#include <bits/stdc++.h>
using namespace std;

int x[21],y[21];

int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	int ans=n;
	for(int bm=0;bm<(1<<n);bm++){
		int cans=0;
		for(int i=0;i<n;i++){
			cans+=(bm&(1<<i))>0;
			bool safe=(bm&(1<<i))>0;
			for(int j=0;j<n;j++){
				safe|=(bm&(1<<j))&&(abs(x[j]-x[i])<=(y[j]-y[i]));
			}
			if(!safe){cans=n;break;}
		}
		ans=min(cans,ans);
	}
	printf("%d",ans);
}
