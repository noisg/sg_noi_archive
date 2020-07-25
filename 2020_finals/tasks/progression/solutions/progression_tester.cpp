#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct node {
    i64 left_s;
    i64 left_c;
    i64 right_s; // the value of the rightmost elem
    i64 right_c;
    int left_len;
    int right_len;
    int curr_len;
    // these have already been pre-applied to the above info
    bool is_override;
    i64 push_s;
    i64 push_c;
};
constexpr int DEPTH = 19;
node stree[1 << (DEPTH + 1)];
void construct(int i){
    node& me = stree[i];
    node& left=stree[i<<1];
    node& right=stree[(i<<1)+1];
    const int mylen = 1 << (__builtin_clz(i) - (31 - DEPTH));
    const int childlen = mylen >> 1;

    if (childlen==1) {
        right.right_c = left.left_c = right.left_c = left.right_c = right.left_s - left.right_s;
    }
    me.curr_len=max(left.curr_len,right.curr_len);
    int lmergelen =
        (right.left_s - left.right_s == left.right_c)
            ? ((right.left_c == left.right_c) ? right.left_len : 1)
            : 0;
    int rmergelen =
        (right.left_s - left.right_s == right.left_c)
            ? ((right.left_c == left.right_c) ? left.right_len : 1)
            : 0;
    me.curr_len = max(me.curr_len, max(left.right_len + lmergelen, right.left_len + rmergelen));
    me.left_s = left.left_s;
    me.left_c = left.left_c;
    if(left.left_len == childlen) me.left_len = childlen + lmergelen;
    else me.left_len = left.left_len;
    me.right_s = right.right_s;
    me.right_c = right.right_c;
    if(right.right_len == childlen) me.right_len = childlen + rmergelen;
    else me.right_len = right.right_len;
}
void pushdown(int i){
    node& me = stree[i];
    if(me.is_override||me.push_s!=0||me.push_c!=0){
        node& left=stree[i<<1];
        node& right=stree[(i<<1)+1];
        const int mylen = 1 << (__builtin_clz(i) - (31 - DEPTH));
        const int childlen = mylen >> 1;

        if(me.is_override){
            me.is_override=false;
            left.curr_len=childlen;
            left.left_s=me.push_s;
            left.left_c=me.push_c;
            left.left_len=childlen;
            left.right_s=me.push_s+me.push_c*(childlen-1);
            left.right_c=me.push_c;
            left.right_len=childlen;
            left.push_s=me.push_s;
            left.push_c=me.push_c;
            left.is_override=true;
            const i64 tmp_s=me.push_s+me.push_c*childlen;
            right.curr_len=childlen;
            right.left_s=tmp_s;
            right.left_c=me.push_c;
            right.left_len=childlen;
            right.right_s=tmp_s+me.push_c*(childlen-1);
            right.right_c=me.push_c;
            right.right_len=childlen;
            right.push_s=tmp_s;
            right.push_c=me.push_c;
            right.is_override=true;
        }
        else{
            left.left_s+=me.push_s;
            left.left_c+=me.push_c;
            left.right_s+=me.push_s+me.push_c*(childlen-1);
            left.right_c+=me.push_c;
            left.push_s+=me.push_s;
            left.push_c+=me.push_c;
            const i64 tmp_s=me.push_s+me.push_c*childlen;
            right.left_s+=tmp_s;
            right.left_c+=me.push_c;
            right.right_s+=tmp_s+me.push_c*(childlen-1);
            right.right_c+=me.push_c;
            right.push_s+=tmp_s;
            right.push_c+=me.push_c;
        }
        me.push_s=0;
        me.push_c=0;
    }
}
void increment(int i, int l, int r, i64 s, int c){
    node& me = stree[i];
    const int mylen = 1 << (__builtin_clz(i) - (31 - DEPTH));
    const int childlen = mylen >> 1;

    if(l==0&&r==mylen) {
        me.left_s += s;
        me.left_c += c;
        me.right_s += s + static_cast<i64>(c) * (mylen - 1);
        me.right_c += c;
        me.push_s += s;
        me.push_c += c;
        return;
    }
    pushdown(i);
    if (l<childlen) increment(i<<1, l, min(r,childlen), s, c);
    if (r>childlen) increment((i<<1)+1, max(l-childlen,0), r-childlen, s+static_cast<i64>(c)*max(childlen - l, 0), c);
    construct(i);
}
void overwrite(int i, int l, int r, i64 s, int c){
    node& me = stree[i];
    const int mylen = 1 << (__builtin_clz(i) - (31 - DEPTH));
    const int childlen = mylen >> 1;

    if(l==0&&r==mylen) {
        me.curr_len = mylen;
        me.left_s = s;
        me.left_c = c;
        me.left_len = mylen;
        me.right_s = s + static_cast<i64>(c) * (mylen - 1);
        me.right_c = c;
        me.right_len = mylen;
        me.push_s = s;
        me.push_c = c;
        me.is_override = true;
        return;
    }
    pushdown(i);
    if (l<childlen) overwrite(i<<1, l, min(r,childlen), s, c);
    if (r>childlen) overwrite((i<<1)+1, max(l-childlen,0), r-childlen, s+static_cast<i64>(c)*max(childlen - l, 0), c);
    construct(i);
}
int query(int i, int l, int r){
    const node& me = stree[i];
    const int mylen = 1 << (__builtin_clz(i) - (31 - DEPTH));
    const int childlen = mylen >> 1;

    if(l==0&&r==mylen) {
        return me.curr_len;
    }
    const node& left=stree[i<<1];
    const node& right=stree[(i<<1)+1];
    pushdown(i);
    int ans = 0;
    if (l<childlen) ans = max(ans, query(i<<1, l, min(r,childlen)));
    if (r>childlen) ans = max(ans, query((i<<1)+1, max(l-childlen,0), r-childlen));
    if (l<childlen && r>childlen) {
        ans = max(2, ans);
        int lmergelen =
            (right.left_s - left.right_s == left.right_c)
                ? ((right.left_c == left.right_c) ? min(r-childlen,right.left_len) : 1)
                : 0;
        int rmergelen =
            (right.left_s - left.right_s == right.left_c)
                ? ((right.left_c == left.right_c) ? min(childlen-l,left.right_len) : 1)
                : 0;
        ans = max(ans, max(min(childlen-l,left.right_len) + lmergelen, min(r-childlen,right.left_len) + rmergelen));
    }
    return ans;
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q;
    cin>>n>>q;
    for(int i=0;i<n;++i){
        int tmp;
        cin>>tmp;
        stree[(1 << DEPTH) + i].push_s = tmp;
    }
    for(int i=0;i<(1<<DEPTH);++i){
        stree[(1 << DEPTH) + i].is_override = true;
        stree[(1 << DEPTH) + i].curr_len = 1;
        stree[(1 << DEPTH) + i].left_s = stree[(1 << DEPTH) + i].push_s;
        stree[(1 << DEPTH) + i].left_len = 1;
        stree[(1 << DEPTH) + i].right_s = stree[(1 << DEPTH) + i].push_s;
        stree[(1 << DEPTH) + i].right_len = 1;
    }
    for(int i = (1<<DEPTH) - 1; i > 0; --i){
        construct(i);
        //cout<<"DBG "<<i<<endl;
        //cout<< stree[i].curr_len<<' '<<stree[i].left_s<<' '<<stree[i].left_c<<' '<<stree[i].left_len<<' '<<stree[i].right_s<<' '<<stree[i].right_c<<' '<<stree[i].right_len<<endl;
    }
    for(int i=0;i<q;++i){
        int type;
        cin>>type;
        if(type==1){
            int l,r,s,c;
            cin>>l>>r>>s>>c;
            --l;
            increment(1, l, r, s, c);
        }
        else if(type==2){
            int l,r,s,c;
            cin>>l>>r>>s>>c;
            --l;
            overwrite(1, l, r, s, c);
        }
        else if(type==3){
            int l,r;
            cin>>l>>r;
            --l;
            cout<<query(1, l,r)<<'\n';
        }
        /*for(int i = (1<<DEPTH) - 1; i > 0; --i){
            cout<<"DBG "<<i<<endl;
            cout<< stree[i].curr_len<<' '<<stree[i].left_s<<' '<<stree[i].left_c<<' '<<stree[i].left_len<<' '<<stree[i].right_s<<' '<<stree[i].right_c<<' '<<stree[i].right_len<<endl;
        }*/
    }
}
