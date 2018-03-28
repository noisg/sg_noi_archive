#include <bits/stdc++.h>
using namespace std;
pair<int,int> yy[200009];
bool p[200009];
int dc[200009];

struct node{
	int s,e,m,v;
	node *l,*r;
	node(int _s,int _e):s(_s),e(_e),m((_s+_e)/2),v(-2e9){
		if(s==e)return;
		l=new node(s,m);r=new node(m+1,e);
	}
	void up(int x,int uv){
		if(s==e){v=max(v,uv);return;}
		if(x>m)r->up(x,uv);
		else l->up(x,uv);
		v=max(l->v,r->v);
	}
	int qu(int x,int y){
		if(s==x&&e==y)return v;
		if(x>m)return r->qu(x,y);
		if(y<=m)return l->qu(x,y);
		return max(l->qu(x,m),r->qu(m+1,y));
	}
}*root1,*root2;

int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		int a,b;scanf("%d%d",&a,&b);
		dc[i]=a;
		yy[i]=make_pair(b,a);
	}
	sort(dc,dc+n);
	sort(yy,yy+n,greater<pair<int,int> >());
	int ans=0;
	root1=new node(0,n-1);//prefix
	root2=new node(0,n-1);//suffix
	for(int i=0;i<n;i++){
		int y=yy[i].first,x=yy[i].second;
		int x2=lower_bound(dc,dc+n,x)-dc;
		int uv1=x+y,uv2=y-x;
		int q1=-1e9,q2=-1e9;
		if(x2)q1=root1->qu(0,x2-1);
		if(x2!=n-1)q2=root2->qu(x2+1,n-1);
		if(q1<uv1&&q2<uv2){
			ans++;
			root1->up(x2,uv1);
			root2->up(x2,uv2);
		}
	}
	printf("%d",ans);
}
