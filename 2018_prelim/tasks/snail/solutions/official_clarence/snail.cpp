#include <cstdio>
#include <algorithm>
#include <assert.h>
#define INF 1012345678012345678LL
#define BIG 1000000000000LL
using namespace std;
typedef long long ll;
// height, number of phases, phase
ll H;
int N;
ll P[10010];
ll simulate[20010];
ll increment = 0; // increment every cycle
bool printed = 0;
int main(void) {
    scanf("%lld%d", &H, &N);
    assert(1<=H && H<=BIG);
    assert(1<=N && N<=10000);
    for (int i=0;i<N;i++) {
        scanf("%lld", &P[i]);
        assert(-BIG<=P[i] && P[i]<=BIG);
    }
    // simulate for 2 days
    simulate[0] = 0; // height at start of each phase
    for (int i=0;i<2*N;i++) { // people may forget this
        simulate[i+1] = max(simulate[i]+P[i%N], 0LL); // people may leave out max
        if (simulate[i+1] >= H) { // >= is intended
            printf("%d %d\n", i/N, i%N);
            printed = 1;
            break;
        }
    }
    if (!printed) {
        for (int i=0;i<N;i++) {
            increment += P[i]; // should not overflow, but can underflow
            // oh no what if it underflows?
            if (increment <= -H) { // if it ever goes back above 0, then it must be possible within first 2N phases
                printf("-1 -1\n");
                printed = true;
                break;
            }
        }
    }
    if (!printed) {
        // check if it goes negative anywhere
        if (increment <= 0) {
            // not possible anymore
            printf("-1 -1\n");
            printed = true;
        } else {
            ll bestDays = INF;
            int phase = 0;
            for (int i=0;i<N;i++) {
                ll days = 1+(H-simulate[N+i+1]+increment-1)/increment;
                if (bestDays > days) {
                    bestDays = days;
                    phase = i;
                }
            }
            printf("%lld %d\n", bestDays, phase);
            printed = true;
        }
    }
    return 0;
}
