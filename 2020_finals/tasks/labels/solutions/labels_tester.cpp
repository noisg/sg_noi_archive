#include<bits/stdc++.h>

using namespace std;

typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<vvd> vvvd;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
typedef vector<long long> vll;
typedef vector<vll> vvll;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef tuple<int,int,int> iii;

#define pb push_back
#define ctz __builtin_ctz
#define db(x) cerr << #x << "=" << x << endl
#define db2(x, y) cerr << #x << "=" << x << "," << #y << "=" << y << endl
#define db3(x, y, z) cerr << #x << "=" << x << "," << #y << "=" << y << "," << #z << "=" << z << endl
#define all(v) (v).begin(),(v).end()
#define rep(i,n) for(int i=0;i<(n);++i) 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    int a[n];
    for(int i=1;i<n;++i) cin>>a[i];
    int b[n],minx=0,maxx=0;
    b[0]=0;
    rep(i,n) {
        if(i==0) continue;
        b[i]=b[i-1]+a[i];
        minx=min(minx,b[i]);
        maxx=max(maxx,b[i]);
    }
    vi c(n+1,0);
    bool can=maxx-minx==n-1;
    --minx;
    rep(i,n) {
        b[i]-=minx;
        if(!(1<=b[i] && b[i]<=n)) {
            can=0;
        }
    }
    if(!can) cout<<-1<<endl;
    else {
        rep(i,n) {
            printf("%d%c",b[i]," \n"[i==n-1]);
        }
    }
}

