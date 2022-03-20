#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int d = atoi(argv[2]);

    printf("%d %d\n", n, d);
    // number of bugs
    for(int i=1; i<=n; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(1, d/2));
    }
    printf("\n");
    // species type
    for(int i=1; i<=n; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(1,d));
    }
    printf("\n");
    // home of dragonfly
    for(int i=1; i<=d; i++) {
        if(i>1) printf(" ");
        printf("%d", rnd.next(2,n));
    }
    printf("\n");
    for(int i=1; i<n; i++) {
        printf("%d %d\n", i, i+1);
    }
}
