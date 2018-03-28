#include <bits/stdc++.h>
using namespace std;
pair<int,int> y[5009];

int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		int a,b;scanf("%d%d",&a,&b);
		y[i]=make_pair(b,a);
	}
	sort(y,y+n,greater<pair<int,int> >());
	int ans=0;
	for(int i=0;i<n;i++){
		bool pick=1;
		for(int j=0;j<i;j++){
			pick&=(y[j].first-y[i].first)<abs(y[i].second-y[j].second);
		}
		ans+=pick;
	}
	printf("%d",ans);
}
