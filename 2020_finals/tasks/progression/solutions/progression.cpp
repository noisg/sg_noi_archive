#include <iostream>
#include <algorithm>
using namespace std;

int N, Q;
long long D[300010], B[300010];

struct treedata {
    int len; long long val;
    treedata() {}
    treedata(int _len, long long _val): len(_len), val(_val) {}
    static bool cmp(treedata lhs, treedata rhs) {
        return lhs.len < rhs.len;
    }
};

struct qval {
    int len; long long sum;
    treedata prefix, suffix, subarray;
    qval() {}
    qval(long long val) {
        len = 1; sum = val;
        subarray = treedata(0, 0);
        prefix = suffix = treedata(1, val);
    }
    void add(long long val) {
        prefix.val += val;
        suffix.val += val;
        subarray.val += val;
        sum += val * len;
    }
    void set(long long val) {
        prefix.val = suffix.val = subarray.val = val;
        prefix.len = suffix.len = len;
        subarray.len = max(0, len - 2);
        sum = val * len;
    }
};

struct node {
    int S, E, M;
    qval V;
    bool lset;
    long long lazy_set, lazy_add;
    node *L, *R;
    node (int _S, int _E): S(_S), E(_E), M((S + E) / 2) {
        lset = false;
        lazy_set = lazy_add = 0;
        if (S == E) {
            V = qval(B[S]);
            return;
        }
        L = new node(S, M); R = new node(M + 1, E);
        V = combine(L->V, R->V);
    }
    qval combine(qval left, qval right) {
        qval ret;
        ret.len = left.len + right.len;
        ret.sum = left.sum + right.sum;

        ret.prefix = left.prefix;
        if (left.prefix.len == left.len && left.prefix.val == right.prefix.val)
            ret.prefix = treedata(left.len + right.prefix.len, left.prefix.val);

        ret.suffix = right.suffix;
        if (right.suffix.len == right.len && left.suffix.val == right.suffix.val)
            ret.suffix = treedata(right.len + left.suffix.len, right.suffix.val);

        ret.subarray = max(left.subarray, right.subarray, treedata::cmp);
        if (min(left.len - 1, left.suffix.len) > ret.subarray.len)
            ret.subarray = treedata(min(left.len - 1, left.suffix.len), left.suffix.val);
        if (min(right.len - 1, right.prefix.len) > ret.subarray.len)
            ret.subarray = treedata(min(right.len - 1, right.prefix.len), right.prefix.val);
        if (left.suffix.val == right.prefix.val && \
            min(left.len - 1, left.suffix.len) + \
            min(right.len - 1, right.prefix.len) > ret.subarray.len)
            ret.subarray = treedata(min(left.len - 1, left.suffix.len) + \
                min(right.len - 1, right.prefix.len), left.suffix.val);
        return ret;
    }
    void push() {
        if (lset) {
            L->rset(lazy_set);
            R->rset(lazy_set);
            lset = false;
            lazy_set = 0;
        }
        if (lazy_add) {
            L->radd(lazy_add);
            R->radd(lazy_add);
            lazy_add = 0;
        }
    }
    void radd(long long QV) {
        if (lset) V.set(lazy_set += QV);
        else {
            lazy_add += QV;
            V.add(QV);
        }
    }
    void rset(long long QV) {
        lset = true;
        lazy_add = 0;
        V.set(lazy_set = QV);
    }
    qval query(int QS, int QE) {
        if (QS <= S && E <= QE) return V;
        push();
        if (QE <= M) return L->query(QS, QE);
        if (QS > M) return R->query(QS, QE);
        return combine(L->query(QS, M), R->query(M + 1, QE));
    }
    void add(int QS, int QE, long long QV) {
        if (QS <= S && E <= QE) return radd(QV);
        push();
        if (QE <= M) L->add(QS, QE, QV);
        else if (QS > M) R->add(QS, QE, QV);
        else {
            L->add(QS, M, QV);
            R->add(M + 1, QE, QV);
        }
        V = combine(L->V, R->V);
    }
    void set(int QS, int QE, long long QV) {
        if (QS <= S && E <= QE) return rset(QV);
        push();
        if (QE <= M) L->set(QS, QE, QV);
        else if (QS > M) R->set(QS, QE, QV);
        else {
            L->set(QS, M, QV);
            R->set(M + 1, QE, QV);
        }
        V = combine(L->V, R->V);
    }
} *root;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int a = 1; a <= N; ++a) {
        cin >> D[a];
        B[a] = D[a] - D[a - 1];
    }
    root = new node(1, N);
    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int L, R; long long S, C;
            cin >> L >> R >> S >> C;
            root->add(L, L, S);
            if (L != R) root->add(L + 1, R, C);
            if (R != N) root->add(R + 1, R + 1, -(S + (R - L) * C));
        } else if (op == 2) {
            int L, R; long long S, C;
            cin >> L >> R >> S >> C;
            long long old_sum = root->query(L, R).sum;
            long long prefix = (L == 1 ? 0 : root->query(1, L - 1).sum);
            root->set(L, L, S - prefix);
            if (L != R) root->set(L + 1, R, C);
            if (R != N) {
                long long new_sum = (S - prefix) + (R - L) * C;
                root->add(R + 1, R + 1, old_sum - new_sum);
            }
        } else {
            int L, R;
            cin >> L >> R;
            qval ret = root->query(L, R);
            int len = max({ret.prefix.len, ret.subarray.len + 1, ret.suffix.len + 1});
            len = min(len, ret.len);
            cout << len << '\n';
        }
    }
    return 0;
}
