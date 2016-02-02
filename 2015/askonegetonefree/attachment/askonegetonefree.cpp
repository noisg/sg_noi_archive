#include <cstdio>
#include "askonegetonefree.h"
using namespace std;
Answer guess(int N){
    Answer reply;      // reply from Bob
    Answer secrets;    // Your guessed secrets

    //----------  Put your code below  -------------------//
    reply = query(4);
	if (reply.p == 1){
		//   "the secret x is greater or equal to 4 "  
	} else {
		//   "the secret x is smaller than 4 " 
	}
	if (reply.q == 1){
		//   "the secret y is greater or equal to 4 "  
	} else {
		//   "the y is smaller than 4 " 
	}

    reply = query(1);
    reply = query(2);
        
    secrets.p = 3;
    secrets.q = 2;

    //----------    Put your code above -------------------//

	return (secrets);
}
