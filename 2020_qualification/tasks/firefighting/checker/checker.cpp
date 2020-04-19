#include <bits/stdc++.h>
using namespace std;
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
    cerr<<"Output is invalid\n";
    return 0;
}
int main(int argc, char** argv){
    ios_base::sync_with_stdio(false);
    assert(argc>=4);
    ifstream in(argv[1]);
    ifstream generated_out(argv[2]);
    ifstream contestant_out(argv[3]);
    int n;
    long long k;
    in>>n>>k;
    assert(1<=n&&n<=1'000'000);
    assert(1<=k&&k<=1'000'000'000'000'000);
    vector<pair<int, int>>* adjlist=new vector<pair<int, int>>[n];
    for(int i=1;i<n;++i){
        int a,b,w;
        in>>a>>b>>w;
        --a;--b;
        assert(0<=a&&a<n);
        assert(0<=b&&b<n);
        assert(1<=w&&w<=1'000'000'000);
        adjlist[a].emplace_back(b,w);
        adjlist[b].emplace_back(a,w);
    }
    assert(in);
    int c_answer;
    if(!(contestant_out>>c_answer))return invalid_error();
    if(1>c_answer||c_answer>n) return invalid_error();
    {
        priority_queue<pair<long long,int>> c_pq;
        {
            bool* c_arr=new bool[n];
            fill(c_arr,c_arr+n,false);
            for(int i=0;i<c_answer;++i){
                int index;
                if(!(contestant_out>>index))return invalid_error();
                if(1>index||index>n) return invalid_error();
                --index;
                if(c_arr[index]) return invalid_error();
                c_arr[index]=true;
                c_pq.push({k,index});
            }
            delete[] c_arr;
        }
        {
            char ch;
            contestant_out>>ch;
        }
        if(!contestant_out.eof())return invalid_error();
        {
            bool* visited=new bool[n];
            fill(visited,visited+n,false);
            while(!c_pq.empty()){
                pair<long long,int> tmp=c_pq.top();
                c_pq.pop();
                if(visited[tmp.second])continue;
                visited[tmp.second]=true;
                for(const pair<int, int>& pr:adjlist[tmp.second]){
                    if(tmp.first>=pr.second&&!visited[pr.first]){
                        c_pq.push({tmp.first-pr.second,pr.first});
                    }
                }
            }
            if(any_of(visited,visited+n,[](bool x){return !x;})){
                return wrong_answer();
            }
            delete[] visited;
        }
    }
    delete[] adjlist;
    int answer;
    generated_out>>answer;
    assert(generated_out);
    assert(1<=answer&&answer<=n);
    if(answer<c_answer)return wrong_answer();
    if(answer==c_answer)return correct();
    return checker_broken();
}
