#include <bits/stdc++.h>
using namespace std;

vector<vector<char> > board;
vector<vector<int> > psum;
int n,m;
int sum(int a,int b){
    if(a<0 || b<0)return 0;
    a=min(a,n-1);b=min(b,m-1);
    return psum[a][b];
}
int sum(int a,int b,int c,int d){
    return sum(c,d)-sum(a-1,d)-sum(c,b-1)+sum(a-1,b-1);
}

int main(){
    //freopen("hi.txt","r",stdin);
    int k,d;
    scanf("%d%d%d%d",&n,&m,&d,&k);
    board.resize(n);
    psum.resize(n);
    for(int i=0;i<n;i++){
        board[i].resize(m);
        psum[i].resize(m);
    }
    char str[500010];
    for(int i=0;i<n;i++){
        scanf("%s",str);
        for(int j=0;j<m;j++){
            board[i][j]=str[j];
            psum[i][j]=sum(i-1,j)+sum(i,j-1)-sum(i-1,j-1);
            psum[i][j]+=board[i][j]=='S';
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(board[i][j]=='M'){
                ans+=sum(i-d,j-d,i+d,j+d)>=k;
            }
        }
    }
    printf("%d\n",ans);
}
