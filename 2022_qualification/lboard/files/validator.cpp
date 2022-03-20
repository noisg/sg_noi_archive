#include "testlib.h"
 
using namespace std;
 
const int n_max = 1000;


 
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int h = inf.readInt(1, n_max, "n");
    inf.readSpace();
    int w = inf.readInt(1, n_max, "d");
    inf.readEoln();
    for(int i=1; i<=h; i++) {
        for (int j = 1; j<=w; j++) {
            if(j>1) inf.readSpace();
            int z = inf.readInt(-1000000000, 1000000000, "z");
        }
        inf.readEoln();
    }
    inf.readEof();
}
