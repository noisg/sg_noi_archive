#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=300'000;
constexpr int MAXM=300'000;
vector<pair<int,int>>adj[MAXN]; // (target, edgeindex)
vector<pair<int,int>> backadj[MAXN]; // target, edgeindex
int weight[MAXM];
int delta[MAXM];
int direction[MAXM]; // set to the index of the to-direction
long long dist[MAXN];
int liveliness[MAXN];
bool visited[MAXN];
int waiting[MAXN];
vector<int> bridges;
bool isbridge[MAXM];
//long long bridgescore[MAXM];
vector<pair<pair<int,int>, long long>> ranges; // <[begin, end), score>
struct rangepqcmp{
    bool operator()(const pair<long long,int>& a, const pair<long long,int>& b) { return a.first > b.first; }
};
priority_queue<pair<long long,int>, vector<pair<long long,int>>, rangepqcmp> rangepq; // <score, end>
int tracks;
int arc[MAXN];
void dfs1(int index){
    visited[index]=true;
    for(const pair<int,int>& x : backadj[index]){
        liveliness[x.first]++;
        if(!visited[x.first])dfs1(x.first);
    }
}
void dfs2(int index){
    if(waiting[index]+1!=liveliness[index]){
        waiting[index]++;
        return;
    }
    tracks-=waiting[index];
    if(backadj[index].empty())return; // reached the source
    if(tracks==1&&backadj[index].size()==1){
        const int bridge=backadj[index][0].second;
        bridges.push_back(bridge);
        isbridge[bridge]=true;
    }
    tracks+=static_cast<int>(backadj[index].size())-1;
    for(const pair<int,int>& x : backadj[index]){
        dfs2(x.first);
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;++i){
        int a,b,w;
        cin>>a>>b>>w;
        weight[i]=w;
        --a;--b;
        adj[a].emplace_back(b,i);
        adj[b].emplace_back(a,i);
    }
    {
        int best=numeric_limits<int>::min();
        for(int i=m-1;i>=0;--i){
            delta[i]=best;
            best=max(best, weight[i]);
        }
    }
    fill(dist,dist+n,numeric_limits<long long>::max());
    fill(direction,direction+m,-1);
    {
        struct elem{
            int source;
            int target;
            long long distance;
            int edgeindex;
        };
        struct cmp{
            bool operator()(const elem& a, const elem& b) const noexcept{
                return a.distance>b.distance;
            }
        };
        priority_queue<elem,vector<elem>,cmp> pq;
        pq.push({-1,0,0,-1});
        while(!pq.empty()){
            elem tmp=pq.top();
            pq.pop();
            if(dist[tmp.target]!=numeric_limits<long long>::max()){
                if(dist[tmp.target]==tmp.distance){
                    backadj[tmp.target].emplace_back(tmp.source,tmp.edgeindex);
                }
                continue;
            }
            dist[tmp.target]=tmp.distance;
            backadj[tmp.target].emplace_back(tmp.source,tmp.edgeindex);
            for(const pair<int,int>& pr: adj[tmp.target]){
                if(direction[pr.second]==-1){
                    direction[pr.second]=pr.first;
                    pq.push({tmp.target,pr.first,tmp.distance+weight[pr.second],pr.second});
                }
            }
        }
    }
    backadj[0].clear();
    /*for(int i=0;i<n;++i){
        cout<<i<<": ";
        for(const auto& pr:backadj[i]){
            cout<<pr.first<<' '<<pr.second<<"   ";
        }
        cout<<endl;
    }*/
    dfs1(n-1);
    /*cout<<"Liveliness:";
    for(int i=0;i<n;++i){
        cout<<' '<<liveliness[i];
    }
    cout<<endl;*/
    fill(visited,visited+n,false);
    tracks=1;
    liveliness[n-1]=1;
    dfs2(n-1);
    /*cout<<"Bridges:";
    for(auto x:bridges){
        cout<<' '<<x;
    }
    cout<<endl;*/
    if(bridges.empty()){
        cout<<dist[n-1]<<'\n';
        return 0;
    }
    /*for(int x : bridges){
        bridgescore[x]=dist[n-1]+delta[x];
    }*/
    fill(arc,arc+n,numeric_limits<int>::max());
    {
        struct elem{
            int target;
            long long distance;
            int arc;
        };
        struct cmp{
            bool operator()(const elem& a, const elem& b) const noexcept{
                return a.distance>b.distance;
            }
        };
        priority_queue<elem,vector<elem>,cmp> pq;
        pq.push({n-1,0,0});
        while(!pq.empty()){
            elem tmp=pq.top();
            pq.pop();
            if(arc[tmp.target]!=numeric_limits<int>::max()){
                if(arc[tmp.target]>tmp.arc){
                    //cout<<tmp.target<<' '<<tmp.arc<<' '<<tmp.distance<<' '<<dist[tmp.target]<<endl;
                    ranges.push_back({{tmp.arc, arc[tmp.target]}, tmp.distance+dist[tmp.target]});
                    /*for(int i=tmp.arc;i!=arc[tmp.target];++i){
                        bridgescore[bridges[i]]=min(bridgescore[bridges[i]],tmp.distance+dist[tmp.target]);
                    }*/
                }
                continue;
            }
            arc[tmp.target]=tmp.arc;
            for(const pair<int,int>& pr:adj[tmp.target]){
                if(isbridge[pr.second]){
                    pq.push({pr.first,tmp.distance+weight[pr.second],tmp.arc+1});
                }else {
                    pq.push({pr.first,tmp.distance+weight[pr.second],tmp.arc});
                }
            }
        }
    }
    sort(ranges.begin(), ranges.end(), [](const pair<pair<int,int>, long long>& a, const pair<pair<int,int>, long long>& b) {
        return a.first.first < b.first.first;
    });
    long long ans=dist[n-1];
    auto range_it=ranges.begin();
    for(int i=0;i<static_cast<int>(bridges.size());++i){
        long long bmin=dist[n-1]+delta[bridges[i]];
        while(!rangepq.empty()&&rangepq.top().second<=i)rangepq.pop();
        while(range_it!=ranges.end()&&range_it->first.first==i){
            rangepq.push({range_it->second,range_it->first.second});
            ++range_it;
        }
        if(!rangepq.empty())bmin=min(bmin,rangepq.top().first);
        ans=max(ans,bmin);
    }
    /*for(const int x:bridges){
        ans=max(ans,bridgescore[x]);
    }*/
    cout<<ans<<'\n';
}
