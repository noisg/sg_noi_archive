#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=1000000;
long long d[MAXN], v[MAXN+1];
bool shielded[MAXN];
int correct(){
    cout<<"1\n";
    cerr<<"translate:success\n";
    return 0;
}
int checker_broken(){
    cout<<"1\n";
    cerr<<"Checker is broken\n";
    return 0;
}
int wrong_answer(){
    cout<<"0\n";
    cerr<<"translate:wrong\n";
    return 0;
}
int invalid_error(){
    cout<<"0\n";
    cerr<<"Damaged module blocking communication between protected modules\n";
    return 0;
}
int format_error(){
    cout<<"0\n";
    cerr<<"Output format isn't correct\n";
    return 0;
}
int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    assert(argc>=4);
    ifstream in(argv[1]);
    ifstream generated_out(argv[2]);
    ifstream contestant_out(argv[3]);
    int n,s;
    long long k;
    in>>n>>s>>k;
    assert(n<=MAXN);
    assert(s<=n);
    assert(n>=1);
    assert(s>=1);
    assert(k>=1);
    d[0]=0;
    for(int i=1;i<n;++i){
        int tmp;
        in>>tmp;
        d[i]=d[i-1]+tmp;
    }
    v[0]=0;
    for(int i=0;i<n;++i){
        int tmp;
        in>>tmp;
        v[i+1]=v[i]+tmp;
    }
    assert(in);
    long long max_value;
    generated_out>>max_value;
    assert(generated_out);
    assert(max_value>=1);
    int num_shields_deployed;
    if(!(contestant_out>>num_shields_deployed))return format_error();
    if(num_shields_deployed<0||num_shields_deployed>s) return wrong_answer();
    for(int i=0;i<num_shields_deployed;++i){
        int loc;
        if(!(contestant_out>>loc))return format_error();
        --loc;
        if(loc<0||loc>=n)return format_error();
        if(!shielded[loc]){
            shielded[loc]=true;
            for(int x=loc-1;x>=0;--x){
                if(d[loc]-d[x]>k||shielded[x])break;
                shielded[x]=true;
            }
            for(int x=loc+1;x<n;++x){
                if(d[x]-d[loc]>k||shielded[x])break;
                shielded[x]=true;
            }
        }
    }
    char ch;
    contestant_out>>ch;
    if(!contestant_out.eof())return format_error();
    bool* const start = find(shielded,shielded+n,true);
    if(start==shielded+n)return wrong_answer();
    bool* const stop = find(start,shielded+n,false);
    if(find(stop,shielded+n,true)!=shielded+n)return invalid_error();
    const long long ans=v[stop-shielded]-v[start-shielded];
    for(int i=0;i<=n;++i)cout<<v[i]<<' ';
    cout<<endl;
    //cout<<ans<<' '<<max_value;
    if(ans<max_value)return wrong_answer();
    if(ans==max_value)return correct();
    //cout<<ans<<' '<<max_value;
    return checker_broken();
}
