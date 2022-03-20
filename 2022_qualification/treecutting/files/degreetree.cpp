#include "testlib.h"
#include <list>
#include <unordered_set>
using namespace std;

vector<pair<int,int>> generate_degree_tree(int n) {
    vector<pair<int,int>> adj;
    unordered_set<int> used;
    
    int root = rnd.next(0, n - 1);
    used.insert(root);
    int deg = rnd.next(3, n - 1);
    vector<int> path;
    for (int i = 0; i < deg; i++) path.push_back(root);
    for (int i = 0; i < n; i++) {
        if (i == root) continue;
        int g = rnd.next(0, deg - 1);
        adj.emplace_back(i, path[g]);
        path[g] = i;
    }
    return adj;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    printf("%d\n", n);
    vector<pair<int,int>> g = generate_degree_tree(n);
    for(pair<int,int> p: g) {
        printf("%d %d\n", p.first + 1, p.second + 1);
    }
}
