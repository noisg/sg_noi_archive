#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
unsigned n, m;
vector<unsigned>* adjlist;
unsigned* answer;
void dfs(unsigned index, unsigned prev){
    ++answer[adjlist[index].size()-1];
    for(const unsigned& x : adjlist[index]){
        if(x != prev){
            dfs(x, index);
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    adjlist = new vector<unsigned>[n+m];
    for(unsigned i=1; i<n+m; ++i){
        unsigned x, y;
        cin >> x >> y;
        --x;
        --y;
        adjlist[x].push_back(y);
        adjlist[y].push_back(x);
    }
    answer = new unsigned[n+1];
    fill_n(answer,n+1,0);
    dfs(adjlist[0].front(),0);
    unsigned i=n;
    for(; answer[i]==0 && i>1; --i);
    for(; i>1; --i){
        cout << i << ' ' << answer[i] << '\n';
        answer[i-1] += answer[i];
    }
    delete[] answer;
    delete[] adjlist;
}
