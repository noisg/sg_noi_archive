#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using stat_tree = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

struct result_t{
    stat_tree* tree;
    int ans;
    int fact;
};

constexpr int MOD = 1'000'000'007;

result_t solve(int n){
    if(n == 0) return {new stat_tree, 0, 1};
    int curr;
    cin>>curr;
    result_t res = solve(n - 1);
    int index = res.tree->order_of_key(curr);
    res.tree->insert(curr);
    res.ans = (int)((res.ans + (long long)index * res.fact) % MOD);
    res.fact = (int)((long long)res.fact * n % MOD);
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    cout<<(solve(n).ans + 1) % MOD;
}
