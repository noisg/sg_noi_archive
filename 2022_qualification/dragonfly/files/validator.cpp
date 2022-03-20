#include "testlib.h"

using namespace std;

const int n_max = 5e5;
const int d_max = 3e6;

void verify_tree(int n) {
    vector<int> parent(n+1);
    for(int i=1; i<=n; i++) {
        parent[i] = i;
    }
    for(int i=1; i<=n-1; i++) {
        int u,v;
        u = inf.readInt(1, n, "u");
        inf.readSpace();
        v = inf.readInt(1, n, "v");
        inf.readEoln();
        while(u != parent[u]) {
            u = parent[u] = parent[parent[u]];
        }
        while(v != parent[v]) {
            v = parent[v] = parent[parent[v]];
        }
        ensuref(u != v, "not a tree");
        parent[u] = v;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, n_max, "n");
    inf.readSpace();
    int d = inf.readInt(1, d_max, "d");
    inf.readEoln();
    for(int i=1; i<=n; i++) {
        if(i>1) inf.readSpace();
        int b = inf.readInt(0, (int)d, "b");
    }
    inf.readEoln();
    for(int i=1; i<=n; i++) {
        if(i>1) inf.readSpace();
        int s = inf.readInt(1, n, "s");
    }
    inf.readEoln();
    for(int i=1; i<=d; i++) {
        if(i>1) inf.readSpace();
        int h = inf.readInt(2, n, "h");

    }
    inf.readEoln();
    verify_tree(n);
    inf.readEof();
}
