#include<cstdio>
#include<utility>
#include<algorithm>
using namespace std;
const int MAXN = 1000050;
int N;
pair<long long, long long> pt[MAXN];
long long cnt_sum(long long x, long long y) {
    long long res = 0;
    for (int i = 0; i < N; ++i) {
        res += abs(x-pt[i].first) + abs(y-pt[i].second);
    }
    return res;
}
void exitWithCode(int code){
    if (code == 1) printf("100\n"); //AC
    else printf("0\n");     //WA
    exit(0);
}
int main(int argc, char * argv[])
{
    FILE *input = fopen(argv[1], "r");  //input
    FILE *testOutput = fopen(argv[3], "r"); //user output
    FILE *output = fopen(argv[2], "r"); //tc output
    fscanf(input, "%d", &N);
    for (int i = 0, x, y; i < N; ++i) {
        fscanf(input, "%d%d", &x, &y);
        pt[i] = make_pair(x, y);
    }
    
    long long ox, oy;
    if(fscanf(testOutput, "%lld%lld", &ox, &oy) != 2){
        exitWithCode(0);
    }
    if (ox < 0 || oy < 0 || ox > 1000000000ll || oy > 1000000000ll) {
        exitWithCode(0);
    }
    long long ax, ay;
    fscanf(output, "%lld%lld", &ax, &ay);
    long long as = cnt_sum(ax, ay);
    long long os = cnt_sum(ox, oy);
    
    if (os > as) {
        exitWithCode(0);
    }
    else if (as == os) {
        exitWithCode(1);    //AC
    }
    else {  //should not happen. 
        exitWithCode(0);    //User gets better place than judge
    }
    
}
