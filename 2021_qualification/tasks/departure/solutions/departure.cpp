#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN=1'000'000;
constexpr int MAXM=1'000'000;
pair<long long,long long> buses[MAXN]; // start, end
pair<long long,long long> answers[MAXM];
pair<int,long long> homes[MAXM]; // index, location
inline long long do_gcd(long long a, long long b) {
    if (a<0)a=-a;
    do {
        long long c=a%b;
        a=b;
        b=c;
    } while (b!=0);
    return a;
}
inline pair<long long, long long> intersect(const pair<long long,long long>& p1, const pair<long long,long long>& p2) {
    return {p1.first*p2.second - p2.first*p1.second, p2.second - p1.second + p1.first - p2.first};
}
template <typename Compare>
inline bool elim(const pair<long long,long long>& target, const pair<long long,long long>& base, const pair<long long,long long>& fresh, Compare&& comp) {
    auto [target_a, target_b] = intersect(target, base);
    auto [fresh_a, fresh_b] = intersect(fresh, base);
    return !comp(fresh_a*target_b, target_a*fresh_b);
}
inline bool smaller(const pair<long long,long long>& target, const pair<long long,long long>& base, long long x) {
    auto [target_a, target_b] = intersect(target, base);
    return target_a <= x * target_b;
}
template <typename BusIt, typename HomeIt, typename Compare>
inline void solve(BusIt bus_begin, BusIt bus_end, HomeIt home_begin, HomeIt home_end, Compare&& comp) {
    // sort the buses by start time
    sort(bus_begin, bus_end, [&](const pair<long long,long long>& a, const pair<long long,long long>& b) {
        return comp(a.first, b.first);
    });
    // sort the homes
    sort(home_begin, home_end, [&](const pair<int,long long>& a, const pair<int,long long>& b) {
        return comp(a.second, b.second);
    });
    // do the algorithm
    long long marker = 0; // where the people currently are
    long long fulldays = 0;
    for (; bus_begin != bus_end; ++fulldays) {
        vector<pair<long long,long long>> hull_buses;
        long long new_marker = 0;
        for (; bus_begin != bus_end && !comp(marker, bus_begin->first); ++bus_begin) {
            const long long speed = bus_begin->second - bus_begin->first;
            while (!hull_buses.empty() && !comp(speed, hull_buses.back().second - hull_buses.back().first)) {
                hull_buses.pop_back();
            }
            while (hull_buses.size()>=2 && elim(hull_buses.back(), hull_buses[hull_buses.size()-2], *bus_begin, comp)) {
                hull_buses.pop_back();
            }
            new_marker = max(new_marker, bus_begin->second, comp);
            hull_buses.push_back(*bus_begin);
        }
        assert(!hull_buses.empty() || home_begin == home_end);
        for (; home_begin != home_end; ++home_begin) {
            while (hull_buses.size()>=2 && smaller(hull_buses.back(), hull_buses[hull_buses.size()-2], home_begin->second)) {
                hull_buses.pop_back();
            }
            if(comp(hull_buses.back().second, home_begin->second)) {
                break;
            }
            pair<long long, long long>& ans = answers[home_begin->first];
            if (comp(0,1)){
                ans.second = hull_buses.back().second - hull_buses.back().first;
                ans.first = home_begin->second - hull_buses.back().first;
            }
            else {
                ans.second = hull_buses.back().first - hull_buses.back().second;
                ans.first = hull_buses.back().first - home_begin->second;
            }
            ans.first += fulldays * ans.second;
            const long long gcdval = do_gcd(ans.first, ans.second);
            ans.first /= gcdval;
            ans.second /= gcdval;
        }
        marker = new_marker;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    assert(1<=n&&n<=1'000'000);
    assert(1<=m&&m<=1'000'000);
    pair<long long,long long>* buses_end = buses;
    for(int i=0;i<n;++i){
        cin >> buses_end->first >> buses_end->second;
        assert(-1'000'000<=buses_end->first&&buses_end->first<=1'000'000);
        assert(-1'000'000<=buses_end->second&&buses_end->second<=1'000'000);
        assert(buses_end->first!=buses_end->second);
        ++buses_end;
    }
    auto buses_mid = partition(buses, buses_end, [](const pair<long long,long long>& bus) {
        return bus.second < bus.first; // bus going left
    });
    pair<int,long long>* homes_end = homes;
    for(int i=0;i<m;++i){
        homes_end->first = i;
        cin >> homes_end->second;
        assert(-1'000'000<=homes_end->second&&homes_end->second<=1'000'000);
        assert(homes_end->second!=0);
        ++homes_end;
    }
    auto homes_mid = partition(homes, homes_end, [](const pair<int,long long>& home) {
        return home.second < 0; // home on left
    });
    solve(make_reverse_iterator(buses_mid), make_reverse_iterator(buses), make_reverse_iterator(homes_mid), make_reverse_iterator(homes), std::greater<>{});
    solve(buses_mid, buses_end, homes_mid, homes_end, std::less<>{});
    for (int i=0;i<m;++i){
        assert(answers[i].second>0); // all answers get filled
        cout << answers[i].first << ' ' << answers[i].second << '\n';
    }
}
