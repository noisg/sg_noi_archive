#include "archaeologist.h"
#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int>* children, int* weight, int index) {
    if (children[index].empty()) {
        return weight[index] = 1;
    }
    int ct = 0;
    for (int x : children[index]) {
        ct += dfs(children, weight, x);
    }
    return weight[index] = ct;
}

void archaeologist(int N, int K, int L, std::vector<int> map, int lightlevel, std::vector<int> paths) {
    vector<vector<int>> children(N, vector<int>());
    for (int i=1;i<N;++i) {
        children[map[i]].push_back(i);
    }
    vector<int> weight(N, 0);
    dfs(children.data(), weight.data(), 0);
    int curr = 0;
    int currlight = lightlevel;
    vector<int> currpaths = move(paths);
    int depth = 0;
    while (!children[curr].empty()) {
        assert(children[curr].size() == currpaths.size());
        int estimate = 0;
        if (any_of(currpaths.begin(), currpaths.end(), [](int y) { return y == 0; })) {
            for (int x : children[curr]) {
                estimate += min(weight[x], depth + 1);
            }
            for (int y : currpaths) {
                estimate -= (y != 0);
            }
        }
        else {
            for (int y : currpaths) {
                estimate += L - y;
            }
        }
        if (estimate <= depth) {
            --estimate;
            estimate = L - estimate;
            if (currlight != estimate) set_light(estimate);
        }
        auto minit = min_element(currpaths.begin(), currpaths.end());
        auto [newroom, newpaths] = take_path(static_cast<int>(minit - currpaths.begin()));
        curr = newroom;
        currlight = *minit;
        currpaths = move(newpaths);
        ++depth;
    }
    assert(currlight == 0);
    set_light(L);
}
