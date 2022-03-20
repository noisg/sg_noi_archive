#include "testlib.h"
#define REP(i, n) for(int i = 0; i < n; i ++)
#define REPL(i,m, n) for(int i = m; i < n; i ++)
#include <bits/stdc++.h>
using namespace std;
typedef double ld;
const int MAXINT = 1000000000;
void generateTest(int h, int w, int noneg, int allneg) {
	cout<<h<<" "<<w<<endl;
	for(int i = 0; i < h; i ++) {
		for(int j = 0; j < w; j ++) {
			if (allneg == 1) {
				cout<<rnd.next(-MAXINT, -1);
			} else if (noneg == 1) {
				cout<<rnd.next(0, MAXINT);
			} else {
				cout<<rnd.next(-MAXINT, MAXINT);
			}
					if (j != w-1) {cout<<' ';
		    
		}else {cout<<endl;}
		}

	}
}
int main(int argc, char* argv[])
{
	registerGen(argc, argv, 1);
    int h = atoi(argv[1]);
    int w = atoi(argv[2]);
    int noneg = atoi(argv[3]);
    int allneg = atoi(argv[4]);
    generateTest(h,w,noneg,allneg);
	/*freopen("1.in", "w", stdout);
	generateTest(10,10);
	freopen("2.in", "w", stdout);
	generateTest(100,100);
	freopen("3.in", "w", stdout);
	generateTest(1000,1000);
	freopen("4.in", "w", stdout);
	generateTest(3000,3000);*/
	//freopen("4.in", "w", stdout);

}
