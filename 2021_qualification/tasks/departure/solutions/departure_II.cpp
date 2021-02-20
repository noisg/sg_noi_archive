#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, long long> > A, B, l, m, f, dq;
vector<pair<long long, pair<long long, long long> > > r;
pair<long long, long long> p, q;

inline long long sc() {
    long long i = 0;
    char c;
    bool e;
    while ((c = getchar()) != '-' && (c < '0' || '9' < c));
    if (!(e = (c == '-'))) i = c - '0';
    while ((c = getchar()) != EOF && '0' <= c && c <= '9') i *= 10, i += c - '0';
    return e ? -i : i;
}

inline long long gcd(long long a, long long b) {long long c; while (b) c = b, b = a % b, a = c; return a;}

int main() {
    long long N = sc(), M = sc(), t, a, b, c, d, g, i, j, k;
    for (i = 0; i < N; ++i) a = sc(), b = sc(), a < b ? l.emplace_back(a, b) : m.emplace_back(-a, -b);
    for (i = 0; i < M; ++i) (a = sc()) > 0 ? A.emplace_back(a, i) : B.emplace_back(-a, i);
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sort(l.begin(), l.end());
    sort(m.begin(), m.end());
    for (i = j = t = c = d = 0; i < A.size(); ++t) {
        while (j < l.size() && l[j].first <= c) f.emplace_back(l[j].second - l[j].first, -l[j].first), d = max(d, l[j++].second);
        sort(f.begin(), f.end());
        for (k = 0; k < f.size(); ++k) if (!k || f[k - 1].first < f[k].first) {
            p = f[k];
            if (dq.empty()) {dq.push_back(p); continue;}
            q = dq.back();
            dq.pop_back();
            while (!dq.empty() && (dq.back().first * p.second - p.first * dq.back().second) * (q.first - dq.back().first) <= (dq.back().first * q.second - q.first * dq.back().second) * (p.first - dq.back().first)) q = dq.back(), dq.pop_back();
            dq.push_back(q);
            dq.push_back(p);
        }
        for (k = 0; i < A.size() && A[i].first <= d; ++i) {while (k < dq.size() - 1 && (A[i].first + dq[k].second) * dq[k + 1].first >= (A[i].first + dq[k + 1].second) * dq[k].first) ++k; r.emplace_back(A[i].second, make_pair(t * dq[k].first + A[i].first + dq[k].second, dq[k].first));}
        dq.clear();
        f.clear();
        c = d;
    }
    swap(A, B);
    swap(l, m);
    for (i = j = t = c = d = 0; i < A.size(); ++t) {
        while (j < l.size() && l[j].first <= c) f.emplace_back(l[j].second - l[j].first, -l[j].first), d = max(d, l[j++].second);
        sort(f.begin(), f.end());
        for (k = 0; k < f.size(); ++k) if (!k || f[k - 1].first < f[k].first) {
            p = f[k];
            if (dq.empty()) {dq.push_back(p); continue;}
            q = dq.back();
            dq.pop_back();
            while (!dq.empty() && (dq.back().first * p.second - p.first * dq.back().second) * (q.first - dq.back().first) <= (dq.back().first * q.second - q.first * dq.back().second) * (p.first - dq.back().first)) q = dq.back(), dq.pop_back();
            dq.push_back(q);
            dq.push_back(p);
        }
        for (k = 0; i < A.size() && A[i].first <= d; ++i) {while (k < dq.size() - 1 && (A[i].first + dq[k].second) * dq[k + 1].first >= (A[i].first + dq[k + 1].second) * dq[k].first) ++k; r.emplace_back(A[i].second, make_pair(t * dq[k].first + A[i].first + dq[k].second, dq[k].first));}
        dq.clear();
        f.clear();
        c = d;
    }
    sort(r.begin(), r.end());
    for (i = 0; i < M; ++i) g = gcd(r[i].second.first, r[i].second.second), printf("%lld %lld\n", r[i].second.first / g, r[i].second.second / g);
    return 0;
}
