#include <bits/stdc++.h>

using namespace std;

pair<int,bool> p[100009];

pair<int,bool> fp(int x){
	if(p[x].first==x)return make_pair(x, 0);
	pair<int,bool> xpar = fp(p[x].first);
	return p[x] = make_pair(xpar.first, xpar.second^p[x].second);
}

void mg(int x,int y,bool r){
	pair<int,bool> xpar = fp(x), ypar = fp(y);
	if (xpar.first == ypar.first) return;
	p[xpar.first]= make_pair(ypar.first, r^xpar.second^ypar.second); 
}

int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i = 0; i < n; i++) p[i] = make_pair(i, 0);
	for (int i = 0; i < q; i++) {
		char t;
		int a,b;
		scanf(" %c%d%d",&t,&a,&b);a--;b--;
		if (t=='Q') {
			pair<int,bool> apar = fp(a), bpar = fp(b);
			if (apar.first !=bpar.first) puts("?");
			else {
				puts((apar.second != bpar.second)?"A":"R");
			}
		}
		else mg(a,b,t=='A');
	}
}
