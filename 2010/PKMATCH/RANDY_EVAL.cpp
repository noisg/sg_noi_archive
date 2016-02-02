#include <iostream>
#include <fstream>

#include "MersenneTwister.h"

using namespace std;

const int N=6;
const int M=64;

int T[10][10];
int VERBOSE;
int MatchTotal;
MTRand rny;



void init(int MATCH)
{

for (int i=0; i<N; i++)
for (int j=0; j<N; j++)
{
  T[i][j]=j;  T[j][i]=j;
  if (rny.randInt()%2 == 0)  {T[i][j]=i; T[j][i]=i;}
  if (i==j) {T[i][j]=i;}
}

if (MATCH ==1)
{
T[0][0]=0; T[0][1]=1; T[0][2]=2; T[0][3]=3; T[0][4]=4; T[0][5]=5;
T[1][0]=1; T[1][1]=1; T[1][2]=2; T[1][3]=3; T[1][4]=4; T[1][5]=5;
T[2][0]=2; T[2][1]=2; T[2][2]=2; T[2][3]=3; T[2][4]=4; T[2][5]=5;
T[3][0]=3; T[3][1]=3; T[3][2]=3; T[3][3]=3; T[3][4]=4; T[3][5]=5;
T[4][0]=4; T[4][1]=4; T[4][2]=4; T[4][3]=4; T[4][4]=4; T[4][5]=5;
T[5][0]=5; T[5][1]=5; T[5][2]=5; T[5][3]=5; T[5][4]=5; T[5][5]=5;
}

   //-----------  INTERACT ------------
    for (int i=0; i<N; i++)
    {
      for (int j=0; j<N; j++)  cout << T[i][j] << "  ";
      cout << endl;
    }

    if (VERBOSE==1)
    {
        for (int i=0; i<N; i++)
        {
          cerr << "MESSAGE FROM RANDY: ";
          for (int j=0; j<N; j++)  cerr << T[i][j] << "  ";
          cerr << endl;
        }
    }
    //---------   INTERACT END -------

}


int main(int argc, char *argv[])
{

int win;
int TotalWin;
int RandomSeed;

ifstream fin(argv[1], ifstream::in);
fin >> RandomSeed;

VERBOSE=2;
MatchTotal=5000;
win=0;

// srandom(RandomSeed);
rny.seed(RandomSeed);

for (int MATCH=1;MATCH<=MatchTotal; MATCH++)
{
init( MATCH ) ;

  {
  int Computer, Human;
  int b,a;
  int CMove, HMove;
  double temp;

  Computer=N; Human=N;
  b=M-1;      a=M-1;

  while ( (Computer * Human)>0 )
  { int nodone;

  //---- HUMAN MOVE
     nodone=1;

     //---------   INTERACT START ------------
     cin >> HMove;
     if (VERBOSE==1)  cerr << "MESSAGE FROM YOU  : " << HMove << endl;
     //---------   INTERACT END --------------


     if( ( (1<<HMove)& a )==0)
         { cerr << "MESSAGE FROM RANDY: YOU MADE AN ILLEGAL MOVE!" << endl; break;}


  //----  COMPUTER MOVE
     nodone=1;
     while (nodone) {CMove=   (rny.randInt()%N); if  (  ((1<<CMove)&b) >0 ) {nodone=0;} }
 
     //------------ INTERACT START -----------
     cout << (int) CMove << endl;
     if (VERBOSE==1)  cerr << "MESSAGE FROM RANDY: " << CMove << endl;
     //-----------  INTERACT END -------------

  //--------   U P D A T E      S T A T E  ------------
  if (HMove == CMove )
     {
        a= a^(1<< HMove); b= b^(1<<CMove);
        Computer= Computer-1;
        Human   = Human-1;
        if (VERBOSE==1)  cerr << "...................... both get knocked-out"        << endl;
     }
  else  
  {
  if (T[HMove][CMove] == HMove )     //  Computer win
     {
        a= a^(1<< HMove); 
        Human   = Human-1;
        if (VERBOSE==1)  cerr << "...................... you  get knocked-out"        << endl;
     }
  if (T[HMove][CMove] == CMove )     //  Human win
    {
        b= b^(1<<CMove);
        Computer= Computer-1;
        if (VERBOSE==1)  cerr << "...................... rnd  get knocked-out"        << endl;
    }
  }

  }
  if (Computer==0) win= win+1;

  // ------------  INTERACT START ---------------
  if (Computer==0) 
      {
         cout << "-1" << endl;
         if (VERBOSE==1) cerr << "MESSAGE FROM RANDY: -1 "  << endl;
      }
  else
      {
         cout << "-2" << endl;
         if (VERBOSE==1) cerr << "MESSAGE FROM RANDY: -2" << endl;
      }
  //-------------  INTERACT END ---------------
   
}
}
 cout << win << endl;
 if (VERBOSE==2) cerr << RandomSeed << ": You won " << win << " games " << endl;
}

