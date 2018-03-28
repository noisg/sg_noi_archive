#include <bits/stdc++.h>
using namespace std;

stack<pair<int,int> >s;

int main(){
	int n; cin>>n;
	for(int i=0;i<n;i++){
		int x,y; cin>>x>>y;
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
