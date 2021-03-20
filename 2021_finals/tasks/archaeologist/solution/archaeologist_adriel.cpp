#include "archaeologist.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, vector<int> > ivi;

void archaeologist(int N, int K, int L, std::vector<int> map, int lightlevel, std::vector<int> paths) {
    vector<vector<int> > adjlist; //stores children only
    vector<int> nol; //number of leaves
    int curr = 0; //current room
    for(int i = 0; i < N; ++i){
        vector<int> x;
        adjlist.push_back(x);
        nol.push_back(0);
    }
    for(int i = 1; i < N; ++i){
        adjlist[map[i]].push_back(i);
    }
    //dp(adjlist, 0, nol, -1);
    queue<int> tov;
    vector<int> noch;
    for(int i = 0; i < N; ++i){
        noch.push_back(adjlist[i].size());
        if(adjlist[i].size() == 0){
            tov.push(i);
            nol[i]++;
        }
    }
    while(!tov.empty()){
        int ving = tov.front();
        tov.pop();
        for(int i = 0; i < adjlist[ving].size(); ++i){
            nol[ving] += nol[adjlist[ving][i]];
        }
        if(map[ving] != -1){
            noch[map[ving]]--;
            if(noch[map[ving]] == 0){
                tov.push(map[ving]);
            }
        }
    }
    vector<int> npaths;
    for(int i = 0; i < paths.size(); ++i) npaths.push_back(paths[i]);
    while(!npaths.empty()){
        int has0 = -1; //which subtree isn't visited
        int tv = 0; //subtrees visited (use if has0)
        int rleft = 0; //leaves left (if all are visited)
        int vac = 0; //which subtree isn't full
        for(int i = 0; i < npaths.size(); ++i){
            rleft += L - npaths[i];
            if(npaths[i] != 0){
                tv++;
            }else{
                has0 = i;
            }
            if(npaths[i] != L){
                vac = i;
            }
        }
        ivi nwloc;
        if(has0 == -1){
            set_light(min(max(L - rleft + 1, 0), L));
            nwloc = take_path(vac);
        }else{
            set_light(min(max(0, L - nol[curr] + tv + 1),L));
            nwloc = take_path(has0);
        }
        curr = nwloc.first;
        npaths.clear();
        for(int i = 0; i < nwloc.second.size(); ++i) npaths.push_back(nwloc.second[i]);
    }
    set_light(L);
}