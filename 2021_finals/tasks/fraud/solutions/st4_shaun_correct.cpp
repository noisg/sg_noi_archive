#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pi;
const int MAXN=300005;

int N;
int A[MAXN],B[MAXN];

bool cmp(pi a, pi b){ //return a<b
	assert(a.second>0 && b.second>0);
	return (a.first*b.second < b.first*a.second);
}
pi fmin(pi a, pi b){
	assert(a.second>0 && b.second>0);
	if (a.first*b.second < b.first*a.second) return a;
	else return b;
}
pi fmax(pi a, pi b){
	assert(a.second>0 && b.second>0);
	if (a.first*b.second > b.first*a.second) return a;
	else return b;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>N;
	for(int i=0;i<N;i++)cin>>A[i];
	for(int i=0;i<N;i++)cin>>B[i];
	pi low(0,1),up(INT_MAX,1); //lower and upper bounds of X/Y, as fractions
	for(int i=0;i<N-1;i++){ //A[i]*X+B[i]*Y > A[i+1]*X+B[i+1]*Y
		if(A[i]<A[i+1]){ //X/Y < (B[i]-B[i+1])/(A[i+1]-A[i])
			pi cur(B[i]-B[i+1],A[i+1]-A[i]);
			if(cmp(cur,up))up=cur;
		}
		else if(A[i]>A[i+1]){ //X/Y >(B[i+1]-B[i])/(A[i]-A[i+1])
			pi cur(B[i+1]-B[i],A[i]-A[i+1]);
			if(cmp(low,cur))low=cur;
		}
		else{
			if(B[i]<=B[i+1]){
				cout<<"NO\n";
				return 0;
			}
		}
	}
	if(cmp(low,up))cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}
