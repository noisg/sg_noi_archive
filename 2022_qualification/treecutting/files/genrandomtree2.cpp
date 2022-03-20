#include "testlib.h"
using namespace std;

//borrowing from dragonfly
vector<pair<int,int>> generate_random_tree(int n) {
    vector<pair<int,int>> result;
    vector<int> parent(n+1);
    for(int i=1; i<=n; i++) parent[i] = i;
    int connections = 0;
    while(connections < n-1) {
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        int x_p = x;
        int y_p = y;
        while(x_p != parent[x_p]) {
            x_p = parent[x_p] = parent[parent[x_p]];
        }
        while(y_p != parent[y_p]) {
            y_p = parent[y_p] = parent[parent[y_p]];
        }
        if(x_p != y_p) {
            connections++;
            result.push_back(make_pair(x,y));
            parent[x_p] = y_p;
        }
    }
    return result;

}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    printf("%d\n", n);
    vector<pair<int,int>> g = generate_random_tree(n);
    for(pair<int,int> p: g) {
        printf("%d %d\n", p.first, p.second);
    }
}

