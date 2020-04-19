#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=100'000;
vector<pair<int,int>> adjlist[MAXN];
int spec[MAXN];
bool is_spec[MAXN];
pair<int,int> nearest[MAXN]; // dist, owner
int bnear[MAXN];
int main(){
    ios_base::sync_with_stdio(false);
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        --u;--v;
        adjlist[u].emplace_back(v,w);
        adjlist[v].emplace_back(u,w);
    }
    for(int i=0;i<k;++i){
        cin>>spec[i];
        --spec[i];
        is_spec[spec[i]]=true;
    }
    int ansu, ansv, ansdist=numeric_limits<int>::max()>>1, ansother=numeric_limits<int>::max()>>1, ansu1, ansu1dist=numeric_limits<int>::max()>>1, ansu2dist=numeric_limits<int>::max()>>1, ansv1, ansv1dist=numeric_limits<int>::max()>>1, ansv2dist=numeric_limits<int>::max()>>1;
    struct pq_item{
        int index;
        int dist;
        int owner;
    };
    struct pq_item_comp{
        bool operator()(const pq_item& a, const pq_item& b) const {
            return a.dist>b.dist;
        }
    };
    struct b_item{
        int index;
        int dist;
    };
    struct b_item_comp{
        bool operator()(const b_item& a, const b_item& b) const {
            return a.dist>b.dist;
        }
    };
    {
        fill(nearest,nearest+n,make_pair(-1,-1));
        priority_queue<pq_item,vector<pq_item>,pq_item_comp> pq;
        for(int i=0;i<k;++i){
            pq.push({spec[i],0,spec[i]});
        }
        while(!pq.empty()){
            pq_item tmp = pq.top();
            pq.pop();
            if(nearest[tmp.index].first!=-1){
                if(nearest[tmp.index].second!=tmp.owner){
                    break;
                }
                continue;
            }
            nearest[tmp.index]={tmp.dist, tmp.owner};
            for(const pair<int,int>& pr : adjlist[tmp.index]) {
                if(nearest[pr.first].first==-1||nearest[pr.first].second!=tmp.owner){
                    int pdist;
                    if(nearest[pr.first].first!=-1&&(pdist=tmp.dist+pr.second+nearest[pr.first].first)<ansdist){
                        ansu=tmp.owner;
                        ansv=nearest[pr.first].second;
                        ansdist=pdist;
                    }
                    pq.push({pr.first,tmp.dist+pr.second,tmp.owner});
                }
            }
        }
    }
    {
        fill(nearest,nearest+n,make_pair(-1,-1));
        priority_queue<pq_item,vector<pq_item>,pq_item_comp> pq;
        for(int i=0;i<k;++i){
            if(spec[i]!=ansu&&spec[i]!=ansv){
                pq.push({spec[i],0,spec[i]});
            }
        }
        while(!pq.empty()){
            pq_item tmp = pq.top();
            pq.pop();
            if(nearest[tmp.index].first!=-1){
                if(nearest[tmp.index].second!=tmp.owner){
                    break;
                }
                continue;
            }
            nearest[tmp.index]={tmp.dist, tmp.owner};
            for(const pair<int,int>& pr : adjlist[tmp.index]) {
                if(nearest[pr.first].first==-1||nearest[pr.first].second!=tmp.owner){
                    if(nearest[pr.first].first!=-1)ansother=min(ansother,tmp.dist+pr.second+nearest[pr.first].first);
                    pq.push({pr.first,tmp.dist+pr.second,tmp.owner});
                }
            }
        }
    }
    {
        fill(bnear,bnear+n,-1);
        bool counter=false;
        priority_queue<b_item,vector<b_item>,b_item_comp> pq;
        pq.push({ansu,0});
        while(!pq.empty()){
            b_item tmp = pq.top();
            pq.pop();
            if(bnear[tmp.index]!=-1)continue;
            if(is_spec[tmp.index]&&tmp.index!=ansu&&tmp.index!=ansv){
                if(!counter){
                    ansu1=tmp.index;
                    ansu1dist=tmp.dist;
                    counter=true;
                }
                else{
                    ansu2dist=tmp.dist;
                    break;
                }
            }
            bnear[tmp.index]=tmp.dist;
            for(const pair<int,int>& pr : adjlist[tmp.index]) {
                if(bnear[pr.first]==-1){
                    pq.push({pr.first,tmp.dist+pr.second});
                }
            }
        }
    }
    {
        fill(bnear,bnear+n,-1);
        bool counter=false;
        priority_queue<b_item,vector<b_item>,b_item_comp> pq;
        pq.push({ansv,0});
        while(!pq.empty()){
            b_item tmp = pq.top();
            pq.pop();
            if(bnear[tmp.index]!=-1)continue;
            if(is_spec[tmp.index]&&tmp.index!=ansu&&tmp.index!=ansv){
                if(!counter){
                    ansv1=tmp.index;
                    ansv1dist=tmp.dist;
                    counter=true;
                }
                else{
                    ansv2dist=tmp.dist;
                    break;
                }
            }
            bnear[tmp.index]=tmp.dist;
            for(const pair<int,int>& pr : adjlist[tmp.index]) {
                if(bnear[pr.first]==-1){
                    pq.push({pr.first,tmp.dist+pr.second});
                }
            }
        }
    }
    cout<<min(ansdist+ansother, (ansu1!=ansv1) ? (ansu1dist+ansv1dist) : min(ansu1dist+ansv2dist, ansu2dist+ansv1dist));
    //cout<<ansu<<' '<<ansv<<' '<<ansdist<<' '<<ansother<<' '<<ansu1<<' '<<ansu1dist<<' '<<ansu2dist<<' '<<ansv1<<' '<<ansv1dist<<' '<<ansv2dist<<endl;
}
