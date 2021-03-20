#include <bits/stdc++.h>
using namespace std;

vector<long long> sgA, v; //segtree values; convex hull j's with at least 1 non-redundant line
vector<pair<long long, long long> > sgD, su; //segtree descendants, sorted array u
long long N, K, A[300000], s[300000], C[300000], sgR[300000]; //adjacent distances, position, sum of augmented time, persistent segtree root indices
pair<long long, long long> u[300000]; //first (rightmost) and last (leftmost) j inclusive where line is not redundant
priority_queue<pair<long long, long long> > pq;
set<long long> st;
set<long long>::iterator it, itl, itr;

long long ql(long long i, long long p, long long l, long long h) { //query for largest index less than or equal p
    //printf("QL %lld <%lld>: %lld (%lld %lld) %lld %lld\n", i, p, i > -1 ? sgA[i] : -1, l, h, i > -1 ? sgD[i].first : -1, i > -1 ? sgD[i].second : -1);
    if (i < 0 || !sgA[i]) return -1;
    if (l >= h) return l <= p ? l : -1;
    long long x;
    if ((l + h) / 2 < p && (x = ql(sgD[i].second, p, (l + h) / 2 + 1, h)) > -1) return x;
    return ql(sgD[i].first, p, l, (l + h) / 2);
}

long long qr(long long i, long long p, long long l, long long h) { //query for smallest index greater than or equal p
    //printf("QR %lld <%lld>: %lld (%lld %lld) %lld %lld\n", i, p, i > -1 ? sgA[i] : -1, l, h, i > -1 ? sgD[i].first : -1, i > -1 ? sgD[i].second : -1);
    if (i < 0 || !sgA[i]) return -1;
    if (l >= h) return l >= p ? l : -1;
    long long x;
    if (p < (l + h) / 2 + 1 && (x = qr(sgD[i].first, p, l, (l + h) / 2)) > -1) return x;
    return qr(sgD[i].second, p, (l + h) / 2 + 1, h);
}

void ust(long long i, long long p, long long v, long long l, long long h) { //segtree persistent update
    //printf("UST %lld <%lld %lld>: %lld (%lld %lld) %lld %lld\n", i, p, v, i > -1 ? sgA[i] : -1, l, h, i > -1 ? sgD[i].first : -1, i > -1 ? sgD[i].second : -1);
    if (p <= l && h <= p) {sgA[i] += v; return;}
    if (p <= (l + h) / 2) {
        if (sgD[i].first < 0) {sgD[i].first = sgA.size(); sgA.push_back(0); sgD.emplace_back(-1, -1);}
        else {sgA.push_back(sgA[sgD[i].first]); sgD.push_back(sgD[sgD[i].first]); sgD[i].first = sgA.size() - 1;}
        ust(sgD[i].first, p, v, l, (l + h) / 2);
    } else {
        if (sgD[i].second < 0) {sgD[i].second = sgA.size(); sgA.push_back(0); sgD.emplace_back(-1, -1);}
        else {sgA.push_back(sgA[sgD[i].second]); sgD.push_back(sgD[sgD[i].second]); sgD[i].second = sgA.size() - 1;}
        ust(sgD[i].second, p, v, (l + h) / 2 + 1, h);
    }
    sgA[i] = (sgD[i].first > -1 ? sgA[sgD[i].first] : 0) + (sgD[i].second > -1 ? sgA[sgD[i].second] : 0);
}

pair<long long, long long> lcr(long long a, long long b, long long c) { //range of j where b is not made redundant by a and c, {a > b > c: line a is left of line b is left of line c}
    long long l = 0, h = K, j, xi1, xi2; //the (i-value) intercept of kL and kR, kL > kR, is ((N - kL - 1)s[kL] - (N - kR - 1)s[kR] + j(s[kL] - s[kR])) / ((N - kL - 1) - (N - kR - 1))
    pair<long long, long long> p = make_pair(K, 0);
    bool e0, eK;
    xi1 = ((N - b - 1) * s[b] - (N - c - 1) * s[c] + 0 * (s[b] - s[c])) / (c - b); //intercept of b with c given j = 0
    xi2 = ((N - a - 1) * s[a] - (N - b - 1) * s[b] + 0 * (s[a] - s[b])) / (b - a); //intercept of a with b given j = 0
    e0 = xi2 < xi1; //line b is not redundant at j = 0 iff xi2 < xi1
    xi1 = ((N - b - 1) * s[b] - (N - c - 1) * s[c] + K * (s[b] - s[c])) / (c - b); //intercept of b with c given j = K
    xi2 = ((N - a - 1) * s[a] - (N - b - 1) * s[b] + K * (s[a] - s[b])) / (b - a); //intercept of a with b given j = K
    eK = xi2 < xi1;
    //printf("%lld %lld %lld: %d %d\n", a, b, c, e0, eK);
    if (!e0 && !eK) return make_pair(-1, K + 1); //line b is always redundant
    if (e0 && eK) return make_pair(K, 0);
    if (!e0) {
        while (l < h) { //this can be done in one long formula but we'll binary search j for clarity
            j = (l + h) / 2;
            xi1 = ((N - b - 1) * s[b] - (N - c - 1) * s[c] + j * (s[b] - s[c])) / (c - b);
            xi2 = ((N - a - 1) * s[a] - (N - b - 1) * s[b] + j * (s[a] - s[b])) / (b - a);
            (xi2 < xi1 ? h : l) = j + !(xi2 < xi1);
            //printf("!e0 %lld %lld [%lld]: %lld %lld %lld | %lld %lld\n", l, h, j, a, b, c, xi1, xi2);
        }
        p.second = (l + h) / 2;
    } else {
        while (l < h) {
            j = (l + h + 1) / 2;
            xi1 = ((N - b - 1) * s[b] - (N - c - 1) * s[c] + j * (s[b] - s[c])) / (c - b);
            xi2 = ((N - a - 1) * s[a] - (N - b - 1) * s[b] + j * (s[a] - s[b])) / (b - a);
            (xi2 < xi1 ? l : h) = j - !(xi2 < xi1);
            //printf("!eK %lld %lld [%lld]: %lld %lld %lld | %lld %lld\n", l, h, j, a, b, c, xi1, xi2);
        }
        p.first = (l + h) / 2;
    }
    return p;
}

long long ins(long long a, long long b) { //first (lowest) k where hull j = a is better than or equal to hull j = b, i.e. C[a] - 2a * s[a] + 2a * s[k] <= C[b] - 2b * s[b] + 2b * s[k], {a > b}
    long long l = K, h = N, k;
    bool e;
    while (l < h) {
        k = (l + h) / 2;
        e = C[a] - 2 * a * s[a] + 2 * a * s[k] <= C[b] - 2 * b * s[b] + 2 * b * s[k];
        (e ? h : l) = k + !e;
    }
    assert((l + h) / 2 < N);
    return (l + h) / 2;
}

int main() {
    //freopen("in.txt", "r", stdin);
    long long a, b, c, f, t = 0, xi1, xi2, i, j, k, l;
    pair<long long, long long> p;
    bool e;
    scanf("%lld %lld", &N, &K);
    --K;
    for (i = 0; i < N - 1; ++i) scanf("%lld", &A[i]), s[i + 1] = s[i] + A[i];
    for (i = 0; i < N; ++i) u[i] = make_pair(K, 0);
    for (k = K; k < N; ++k) st.insert(k);
    for (k = K + 1; k < N - 1; ++k) { //find first j where lines not redundant
        p = lcr(k + 1, k, k - 1);
        pq.emplace(-p.first, k);
    }
    while (!pq.empty()) {
        if (pq.top().first < K && st.find(pq.top().second) != st.end()) { //determine u[k].first, delete k from set, update next left and right lines
            k = pq.top().second;
            u[k].first = -pq.top().first;
            pq.pop();
            st.erase(k);
            it = st.upper_bound(k);
            if (*it < N - 1) {itl = itr = it; pq.emplace(-lcr(*++itl, *it, *--itr).first, *it);}
            --it;
            if (*it > K) {itl = itr = it; pq.emplace(-lcr(*++itl, *it, *--itr).first, *it);}
        } else pq.pop();
    }
    for (k = K; k < N; ++k) st.insert(k);
    for (k = K + 1; k < N - 1; ++k) { //find last j where lines not redundant
        p = lcr(k + 1, k, k - 1);
        pq.emplace(p.second, k);
    }
    while (!pq.empty()) {
        if (pq.top().first && st.find(pq.top().second) != st.end()) {
            k = pq.top().second;
            u[k].second = pq.top().first;
            pq.pop();
            st.erase(k);
            it = st.upper_bound(k);
            if (*it < N - 1) {itl = itr = it; pq.emplace(lcr(*++itl, *it, *--itr).second, *it);}
            --it;
            if (*it > K) {itl = itr = it; pq.emplace(lcr(*++itl, *it, *--itr).second, *it);}
        } else pq.pop();
    }
    //for (i = K + 1; i < N - 1; ++i) printf("%lld %lld %lld: %lld %lld\n", i + 1, i, i - 1, lcr(i + 1, i, i - 1).first, lcr(i + 1, i, i - 1).second);
    //for (i = K; i < N; ++i) printf("%lld (%lld %lld)\n", i, u[i].first, u[i].second);
    for (k = K; k < N; ++k) if (u[k].first >= u[k].second) {su.emplace_back(u[k].first, k); su.emplace_back(u[k].second - 1, -k);}
    sort(su.begin(), su.end());
    for (i = K, l = su.size() - 1; i > -1; --i) {
        sgR[i] = sgA.size();
        sgA.push_back(0);
        sgD.emplace_back(-1, -1);
        if (i < K) {sgA[sgR[i]] = sgA[sgR[i + 1]]; sgD[sgR[i]] = sgD[sgR[i + 1]];}
        for (l; l > -1 && i <= su[l].first; --l) {if (su[l].second > 0) ust(sgR[i], su[l].second, 1, 0, N - 1); else ust(sgR[i], -su[l].second, -1, 0, N - 1);}
    }
    //for (i = 0; i < sgA.size(); ++i) printf("%lld: %lld | %lld %lld\n", i, sgA[i], sgD[i].first, sgD[i].second);
    //for (i = K; i > -1; --i) printf("%lld !! %lld\n", i, sgR[i]);
    //printf("\n");
    for (i = k = l = K, j = 0; i > -1; --i) {
        //printf("%lld %lld %lld %lld\n", i, j, k, l);
        if (i < K) {
            a = C[v[j]] + 2 * v[j] * (s[k] - s[v[j]]) + 2 * (N - k - 1) * (s[k] - s[i]);
            f = qr(sgR[v[j]], k + 1, 0, N - 1);
            while (f > -1) {
                b = C[v[j]] + 2 * v[j] * (s[f] - s[v[j]]) + 2 * (N - f - 1) * (s[f] - s[i]);
                if (a < b) break;
                k = f;
                a = C[v[j]] + 2 * v[j] * (s[k] - s[v[j]]) + 2 * (N - k - 1) * (s[k] - s[i]);
                f = qr(sgR[v[j]], k + 1, 0, N - 1);
            } //walk a to the optimal line of j
            while (j < v.size() - 1) {
                l = qr(sgR[v[j + 1]], l, 0, N - 1);
                a = C[v[j + 1]] + 2 * v[j + 1] * (s[l] - s[v[j + 1]]) + 2 * (N - l - 1) * (s[l] - s[i]);
                f = qr(sgR[v[j + 1]], l + 1, 0, N - 1);
                while (f > -1) {
                    b = C[v[j + 1]] + 2 * v[j + 1] * (s[f] - s[v[j + 1]]) + 2 * (N - f - 1) * (s[f] - s[i]);
                    if (a < b) break;
                    l = f;
                    a = C[v[j + 1]] + 2 * v[j + 1] * (s[l] - s[v[j + 1]]) + 2 * (N - l - 1) * (s[l] - s[i]);
                    f = qr(sgR[v[j + 1]], l + 1, 0, N - 1);
                } //walk b to the optimal line of j + 1
                a = C[v[j]] + 2 * v[j] * (s[k] - s[v[j]]) + 2 * (N - k - 1) * (s[k] - s[i]);
                b = C[v[j + 1]] + 2 * v[j + 1] * (s[l] - s[v[j + 1]]) + 2 * (N - l - 1) * (s[l] - s[i]);
                if (a < b) break;
                ++j; //move from j to j + 1
                k = l;
            }
            //printf("%lld (%lld %lld, %lld %lld, %lld %lld): ", i, v[j], k, qr(sgR[v[j]], k + 1, 0, N - 1) > -1 ? v[j] : -1, qr(sgR[v[j]], k + 1, 0, N - 1), j < v.size() - 1 ? v[j + 1] : -1, j < v.size() - 1 ? l : -1);
            //printf("%lld %lld %lld\n", C[v[j]] + 2 * v[j] * (s[k] - s[v[j]]) + 2 * (N - k - 1) * (s[k] - s[i]), qr(sgR[v[j]], k + 1, 0, N - 1) > -1 ? C[v[j]] + 2 * v[j] * (s[qr(sgR[v[j]], k + 1, 0, N - 1)] - s[v[j]]) + 2 * (N - qr(sgR[v[j]], k + 1, 0, N - 1) - 1) * (s[qr(sgR[v[j]], k + 1, 0, N - 1)] - s[i]) : -1, j < v.size() - 1 ? C[v[j + 1]] + 2 * v[j + 1] * (s[l] - s[v[j]]) + 2 * (N - l - 1) * (s[l] - s[i]) : -1);
            C[i] = C[v[j]] + 2 * v[j] * (s[k] - s[v[j]]) + 2 * (N - k - 1) * (s[k] - s[i]);
        }
        //if (!v.empty() && C[v.back()] - 2 * v.back() * s[v.back()] + 2 * v.back() * s[N - 1] <= C[i] - 2 * i * s[i] + 2 * i * s[N - 1]) {printf("?\n\n"); continue;}
        if (!v.empty() && C[v.back()] - 2 * v.back() * s[v.back()] + 2 * v.back() * s[N - 1] <= C[i] - 2 * i * s[i] + 2 * i * s[N - 1]) continue; //new j provides no optimal lines
        while (v.size() > 1) { //delete previous j's which are now redundant
            a = qr(sgR[i], ins(i, v.back()), 0, N - 1); //rightmost line of i before i <-> v.back() intersection
            b = ins(v.back(), v[v.size() - 2]);
            c = ql(sgR[v[v.size() - 2]], b - 1, 0, N - 1); //rightmost line of v.back() before v.back() <-> v[v.size() - 2] intersection
            b = qr(sgR[v.back()], b, 0, N - 1); //leftmost line of v[v.size() - 2] before v.back() <-> v[v.size() - 2] intersection
            //printf("(%lld %lld) (%lld %lld) (%lld %lld)\n", i, a, v.back(), b, v[v.size() - 2], c);
            if (a <= b) {v.pop_back(); continue;}
            xi1 = ((N - b - 1) * s[b] - (N - c - 1) * s[c] + v.back() * s[b] - v[v.size() - 2] * s[c] + C[v.back()] / 2 - C[v[v.size() - 2]] / 2 - v.back() * s[v.back()] + v[v.size() - 2] * s[v[v.size() - 2]]) / (c - b); //i <-> v.back() intersection point
            xi2 = ((N - a - 1) * s[a] - (N - b - 1) * s[b] + i * s[a] - v.back() * s[b] + C[i] / 2 - C[v.back()] / 2 - i * s[i] + v.back() * s[v.back()]) / (b - a); //v.back() <-> v[v.size() - 2] intersection point
            //printf("_%lld %lld\n", xi1, xi2);
            if (xi1 <= xi2) v.pop_back();
            else break;
        }
        v.push_back(i);
        //for (long long z = 0; z < v.size(); ++z) printf("!%lld\n", v[z]);
        //printf("\n");
    }
    //for (i = 0; i < K + 1; ++i) printf("%lld%c", C[i], i < K ? ' ' : '\n');
    for (i = 0; i < N; ++i) t += abs(s[K] - s[i]);
    printf("%lld", C[0] + t);
    return 0;
}
