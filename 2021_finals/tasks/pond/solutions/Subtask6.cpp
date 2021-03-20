#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, long long> > su; //sorted array u
long long N, K, A[300000], s[300000], C[300000], sgA[1200000][4]; //adjacent distances; position; sum of augmented time; segment tree: leftmost, closest left of centre, closest right of centre, rightmost
pair<long long, long long> u[300000]; //first (rightmost) and last (leftmost) j inclusive where line is not redundant
priority_queue<pair<long long, long long> > pq;
set<long long> st;
set<long long>::iterator it, itl, itr;

long long qst(long long i, long long pi, long long pj, long long l, long long h) { //query for best line for pj -> k -> pi
    //printf("QST %lld %lld %lld (%lld %lld): %lld %lld %lld %lld\n", i, pi, pj, l, h, sgA[i][0], sgA[i][1], sgA[i][2], sgA[i][3]);
    if (h <= l) return l;
    long long v1, v2;
    v1 = sgA[i][1] > -1 ? (C[pj] + 2 * pj * (s[sgA[i][1]] - s[pj]) + 2 * (N - sgA[i][1] - 1) * (s[sgA[i][1]] - s[pi])) : 1000000000000000000;
    v2 = sgA[i][2] > -1 ? (C[pj] + 2 * pj * (s[sgA[i][2]] - s[pj]) + 2 * (N - sgA[i][2] - 1) * (s[sgA[i][2]] - s[pi])) : 1000000000000000000;
    if (v1 <= v2) return qst(i * 2, pi, pj, l, (l + h) / 2);
    else return qst(i * 2 + 1, pi, pj, (l + h) / 2 + 1, h);
}

void ust(long long i, long long p, long long v, long long l, long long h) { //segtree update
    //printf("UST %lld %lld %lld (%lld %lld): %lld %lld %lld %lld\n", i, p, v, l, h, sgA[i][0], sgA[i][1], sgA[i][2], sgA[i][3]);
    if (p <= l && h <= p) {sgA[i][0] = sgA[i][1] = sgA[i][2] = sgA[i][3] = (v > 0 ? p : -1); return;}
    if (p <= (l + h) / 2) ust(i * 2, p, v, l, (l + h) / 2);
    else ust(i * 2 + 1, p, v, (l + h) / 2 + 1, h);
    sgA[i][0] = sgA[i * 2][0] > -1 ? sgA[i * 2][0] : sgA[i * 2 + 1][0];
    sgA[i][1] = sgA[i * 2][3];
    sgA[i][2] = sgA[i * 2 + 1][0];
    sgA[i][3] = sgA[i * 2 + 1][3] > -1 ? sgA[i * 2 + 1][3] : sgA[i * 2][3];
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

int main() {
    //freopen("in.txt", "r", stdin);
    long long a, b, c, v, t = 0, i, j, k, l;
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
    memset(sgA, -1, sizeof(sgA));
    memset(C, -1, sizeof(C));
    C[K] = 0;
    for (j = K, l = su.size() - 1; j; --j) {
        for (l; l > -1 && j <= su[l].first; --l) {if (su[l].second > 0) ust(1, su[l].second, 1, 0, N - 1); else ust(1, -su[l].second, -1, 0, N - 1);}
        for (i = j - 1; i > -1; --i) {
            k = qst(1, i, j, 0, N - 1);
            v = C[j] + 2 * j * (s[k] - s[j]) + 2 * (N - k - 1) * (s[k] - s[i]);
            //printf("!!%lld %lld: %lld %lld\n", i, j, k, v);
            if (C[i] < 0 || C[i] > v) C[i] = v;
        }
    }
    for (i = 0; i < N; ++i) t += abs(s[K] - s[i]);
    printf("%lld", C[0] + t);
    return 0;
}
