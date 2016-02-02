#include <iostream>
#include "askonegetonefree.h"
using namespace std;
static int N,A,B,steps;
Answer query(int r){
    Answer ret;

    // cout << " Are the numbers greater or equal to " << r << "?   "<< endl ;

	steps = steps + 1;
    ret.p = (X>=r);
    ret.q = (Y>=r);

    // cout << ret.p << "  " << ret.q << endl;
	return (ret);
}

int main(){
       
    Answer your_guess;

    N=4;  
    X=3;  Y=2;        
    steps = 0;

	your_guess = guess(N);

	if (your_guess.p  == X   &&  your_guess.q == Y ){ cout <<"CORRECT!   ";}
	if (your_guess.p  != X   ||  your_guess.q != Y ){ cout <<"WRONG!     ";}

    cout << "The number of questions asked is " << STEPS << endl;
}
