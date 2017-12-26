#include<cstdio>
#include<algorithm>
using namespace std;
const int STSZ = 1<<17;
int st[STSZ << 1];
int arr[100000];
void update(int rs, int re, int rpos, int pos, int val){
    if(re == rs + 1) st[rpos] = val;
    else{
        int mid = (rs + re) / 2;
        if(pos < mid) update(rs, mid, rpos * 2, pos, val);
        else update(mid, re, rpos * 2 + 1, pos, val);
        st[rpos] = min(st[rpos * 2], st[rpos * 2 + 1]);
    }
}
void update(int pos, int val){
    update(0, STSZ, 1, pos, val);
}
int query(int rs, int re, int rpos, int qs, int qe){
    if(rs == qs && re == qe) return st[rpos];
    else{
        int mid = (rs + re) / 2;
        if(qe <= mid) return query(rs, mid, rpos * 2, qs, qe);
        else if (qs >= mid) return query(mid, re, rpos * 2 + 1, qs, qe);
        else return min(
            query(rs, mid, rpos * 2, qs, mid),
            query(mid, re, rpos * 2 + 1, mid, qe)
        );
    }
}
int query(int qs, int qe){
    return query(0, STSZ, 1, qs, qe);
}
void exitWithCode(int code){
    if (code == 0) printf("100\n"); //AC
    else if (code == 1) printf("0\n");  //WA
    else if (code == 2) printf("30\n"); //Partial credit 30%
    exit(0);
}
int main(int argc, char **argv){
    FILE *input = fopen(argv[1], "r");
    FILE *testOutput = fopen(argv[3], "r");
    FILE *output = fopen(argv[2], "r");
    
    int N, Q; fscanf(input, "%d%d", &N, &Q);
    int checkInt; fscanf(output, "%d", &checkInt);
    bool impossible = checkInt == -1;
    bool claimImpossible = true;
    bool negativeOneEncountered = false;
    for(int i = 0; i < N; i++){
        if(fscanf(testOutput, "%d", &arr[i]) != 1){
            exitWithCode(1);
        }
        if(arr[i] == -1) negativeOneEncountered = true;
        else{
            claimImpossible = false;
            if(arr[i] < 0 || arr[i] >= N){
                exitWithCode(1);
            }
            update(i, arr[i]);
        }
    }
    if(negativeOneEncountered && !claimImpossible) exitWithCode(1);
    if(impossible && claimImpossible) exitWithCode(0);
    if(!impossible && claimImpossible) exitWithCode(1);
    for(int i = 0; i < Q; i++){
        int left, right, ans;
        fscanf(input, "%d%d%d", &left, &right, &ans);
        if(query(left, right + 1) != ans){
            //printf("%d, %d gives %d\n", left, right, query(left, right + 1));
            exitWithCode(1);
        }
    }
    sort(arr, arr + N);
    for(int i = 0; i < N; i++){
        if(arr[i] != i){
            exitWithCode(2);
        }
    }
    exitWithCode(0);
}
