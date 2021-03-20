#include "archaeologist.h"
#include <bits/stdc++.h>
using namespace std;

static mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
static int N, K, L;
static vector<vector<int>> adjlist;
static int archaeologist_index;
static int archaeologist_room;
static vector<int> levels;
static vector<bool> explored;

static vector<int> prep_paths(int room) {
    shuffle(adjlist[room].begin(), adjlist[room].end(), rng);
    vector<int> ret;
    ret.reserve(adjlist[room].size());
    for (int x : adjlist[room]) {
        ret.push_back(levels[x]);
    }
    return ret;
}

pair<int, vector<int>> take_path(int corridor) {
    if (!(0 <= corridor && corridor < adjlist[archaeologist_room].size())) {
        cout << "take_path() called with invalid corridor" << endl;
        abort();
    }
    archaeologist_room = adjlist[archaeologist_room][corridor];
    cout << "Taking corridor " << corridor << " to room " << archaeologist_room << endl;
    vector<int> paths = prep_paths(archaeologist_room);
    explored[archaeologist_room] = true;
    return make_pair(archaeologist_room, move(paths));
}

void set_light(int level) {
    if (!(0 <= level && level <= L)) {
        cout << "set_light() called with invalid level" << endl;
        abort();
    }
    cout << "Setting light at " << archaeologist_room << " to " << level << endl;
    levels[archaeologist_room] = level;
}

int main() {
    cin >> N >> K >> L;
    adjlist.assign(N, vector<int>());
    levels.assign(N, 0);
    explored.assign(N, false);
    vector<int> parent(N, 0);
    parent[0] = -1;
    for (int i = 1; i < N; ++i) {
        cin >> parent[i];
        adjlist[parent[i]].push_back(i);
    }
    for (int i = 0; i < K; ++i) {
        cout << "Archaeologist " << i << ":" << endl;
        archaeologist_index = i;
        archaeologist_room = 0;
        vector<int> paths = prep_paths(0);
        explored[0] = true;
        archaeologist(N, K, L, parent, levels[0], move(paths));
    }
    if (!all_of(explored.begin(), explored.end(), [](bool e) { return e; })) {
        cout << "Not all rooms were explored" << endl;
        return 0;
    }
    cout << "All rooms explored successfully" << endl;
    return 0;
}
