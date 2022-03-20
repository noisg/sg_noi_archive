//
//  solution.cpp
//  
//
//  Created by Marc Phua on 4/2/22.
//

#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
//#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
using namespace std;
#define MAXN 300005
#define K 38
#define MAXP 25
#define MAXK 150
#define MAXM 8388610
#define MAXC 255
#define MAXERR 105
#define MAXLEN 105
#define MDIR 10
#define MAXR 705
#define BASE 102240
#define MAXA 28
#define MAXT 100005
#define LIMIT 86400
#define MAXV 305
#define OP 0
#define CLO 1
#define DIG 1
#define C1 0
#define C2 1
#define PLUS 0
#define MINUS 1
#define MUL 2
#define CLO 1
#define VERT 1
#define B 31
#define B2 1007
#define W 1
#define H 22
#define SPEC 1
#define MUL 2
#define CNT 3
#define ITER 1000
#define INF 1e9
#define EPS 1e-12
#define MOD 1000000007
#define CONST 1000000007
#define FACT 100000000000000
#define START 1611516670
#define PI 3.14159265358979
#define CUT 75
typedef long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ll,int> li;
typedef tuple<int,int,int> iii;
typedef vector<vector<int>> vv;
typedef vector<int> vi;
typedef pair<ld,int> iv;
typedef vector<ii> vii;
typedef complex<double> cd;
#define rep(i,x,y) for (int i = (x); i < (y); i++)
#define LSOne(S) (S & (-S))

vv adj;
int dep[MAXN];
void dfs(int u, int p) {
    for (auto &i : adj[u]) {
        if (i == p) continue;
        dfs(i, u);
        dep[u] = max(dep[u], dep[i] + 1);
    }
}

int ans = 0;
void solve(int u, int p, int up, int amax) {
    vector<ii> mst;
    for (auto &v : adj[u]) {
        if (v == p) continue;
        mst.emplace_back(dep[v], v);
    }
    sort(mst.rbegin(), mst.rend());
    if (mst.size() >= 1) {
        ans = max(ans, mst[0].first + 1 + max(amax + 1, 0));
    }
    if (mst.size() >= 2) {
        ans = max(ans, mst[0].first + mst[1].first + 2 + max(amax + 1, 0));
    }
    if (mst.size() >= 3) {
        ans = max(ans, mst[0].first + mst[1].first + mst[2].first + 3);
    }
    
    vector<ii> three;
    three.emplace_back(up, -1);
    //dummy entries here
    three.emplace_back(-1, 0);
    three.emplace_back(-1, 0);
    rep(i,0,min(3,(int)(mst.size()))) three.emplace_back(mst[i]);
    //find the best possible
    sort(three.rbegin(), three.rend());
    for (auto &v : adj[u]) {
        if (v == p) continue;
        if (v == three[0].second) {
            solve(v, u, three[1].first + 1, max(amax, three[1].first + three[2].first + 2));
        } else if (v == three[1].second) {
            solve(v, u, three[0].first + 1, max(amax, three[0].first + three[2].first + 2));
        } else {
            solve(v, u, three[0].first + 1, max(amax, three[0].first + three[1].first + 2));
        }
    }
}

int main() {
    int n; cin >> n;
    adj.resize(n);
    rep(i,0,n-1) {
        int a,b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    solve(0, 0, -1, -INF);
    cout << ans;
}

