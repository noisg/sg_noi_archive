//  PreCompute
//
//  Created by Marc Phua on 4/2/21.
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
#define MAXN 3005
#define MAXM 1005
#define K 38
#define MAXP 25
#define MAXK 150
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
#define H 21
#define SPEC 1
#define MUL 2
#define CNT 3
#define ITER 1000
#define INF 1e18
#define EPS 1e-9
#define MOD 1000000007
#define CONST 1000000007
#define FACT 100000000000000
#define START 1611516670
#define PI 3.14159265358979
#define CUT 75
typedef long long ll;
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

ll row[MAXN][MAXN], col[MAXN][MAXN], a[MAXN][MAXN];
int r,c;
void row_kadane(vector<ll> &v, int rr, bool rev) {
    ll cbst = 0;
    rep(i,0,c) {
        int id = (rev) ? c - i - 1 : i;
        if (cbst < 0) cbst = 0;
        row[rr][id] = max(row[rr][id], cbst + v[i]);
        cbst = cbst + v[i];
    }
}
 
void col_kadane(vector<ll> &v, int cc, bool rev) {
    ll cbst = 0;
    rep(i,0,r) {
        int id = (rev) ? r - i - 1 : i;
        if (cbst < 0) cbst = 0;
        col[id][cc] = max(col[id][cc], cbst + v[i]);
        cbst = cbst + v[i];
    }
}

int main() {
    cin >> r >> c;
    rep(i,0,r) {
        rep(j,0,c) {
            cin >> a[i][j];
            row[i][j] = col[i][j] = -INF;
        }
    }
    rep(i,0,r) {
        vector<ll> v;
        rep(j,0,c) v.emplace_back(a[i][j]);
        rep(j,0,2) {
            row_kadane(v,i,j);
            reverse(v.begin(), v.end());
        }
    }
    
    rep(i,0,c) {
        vector<ll> v;
        rep(j,0,r) v.emplace_back(a[j][i]);
        rep(j,0,2) {
            col_kadane(v,i,j);
            reverse(v.begin(), v.end());
        }
    }
    
    ll ans = -INF;
    rep(i,0,r) {
        rep(j,0,c) ans = max(ans, row[i][j] + col[i][j] - a[i][j]);
    }
    cout << ans;
}
