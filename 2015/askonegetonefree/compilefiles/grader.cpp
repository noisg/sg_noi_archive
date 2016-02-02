#include <cstdio>
#include "askonegetonefree.h"
using namespace std;

static int cost        [1000001];
static int position    [1000001];
static int cost_binary [1000001];
static int A,B,guessA, guessB;
static int N,steps,mode;
static int choice;   // user input

static int MIN_A, MAX_A, MIN_B, MAX_B;

static int min ( int X, int Y)
{ if (X>Y)  {return (Y);}  else {return (X); } }
static int max ( int X, int Y)
{ if (X<Y)  {return (Y);}  else {return (X); } }


static int init()
{
int i,j;

  //  steps for binary search
  cost_binary [0] = 0; cost_binary [1] = 0; cost_binary [2] = 1;
  for (i=3;i<=N; i++ )
    {  cost_binary[i]= cost_binary[ (i+1)/2 ] + 1; }



  //  steps for 2-values search 
  cost [0] = 0;  position[0]=0;
  cost [1] = 0;  position[1]=0;
  cost [2] = 1;  position[2]=1;
  for (i=3;i<=N; i++)
    {
      int bound;

      cost[i] = N+1; 

      bound = min ( i-1,  (i+1)/2 ); 
   
      for (j=1; j<= bound; j++)
         {
          int temp;

          temp = cost_binary [j] + cost_binary[i -j];
          if (temp <  cost[ i-j ] )   {temp = cost[ i-j ];}
          if (temp <  cost[  j  ] )   {temp = cost[   j ];}

          if (temp < cost[i] ) { cost[i] =temp; position[i] = j; }

         }
      cost[i] = 1+ cost[i];
    }

 return (0);
}

Answer query(int r){
	steps++;
	if (mode==1){
		Answer ret;
		ret.p = (int) (A>=r);
		ret.q = (int) (B>=r);
		return ret;
	}

	int r1, r2;
	  
	int cost00,cost01,cost10,cost11;
	int minA[2], maxA[2], minB[2], maxB[2];

	//  if my reply is A < r 
	maxA[0] =   min( MAX_A, r-1);
	minA[0] =   MIN_A;

	//  if my reply is A >= r 
	maxA[1] =   MAX_A;
	minA[1] =   max( r, MIN_A);

	//  if my reply is B < r 
	maxB[0] =   min( MAX_B, r-1);
	minB[0] =   MIN_B;

	//  if my reply is B >= r 
	maxB[1] =   MAX_B;
	minB[1] =   max( r, MIN_B);

	 
	//  C A S E  0  0 
	if ( (maxA[0] < minA[0] )|| (maxB[0] < minB[0]))
		{ cost00 = -1; }
	else
		{ cost00 = cost [ maxA[0] - minA[0] + 1 ]; }

	//  C A S E  1  1 
	if ( (maxA[1] < minA[1] )|| (maxB[1] < minB[1]))
		{ cost11 = -1; }
	else
		{ cost11 = cost [ maxA[1] - minA[1]  + 1]; }

	//  C A S E  0  1 
	if ( (maxA[0]< minA[0])|| (maxB[1]< minB[1]))
		{ cost01 = -1; }
	else
		{ cost01 = cost_binary [ maxA[0]- minA[0]  + 1] + cost_binary[ maxB[1] - minB[1] + 1] ;}

	//  C A S E  1  0 
	if ( (maxA[1]< minA[1])|| (maxB[0]< minB[0]))
		{ cost10 = -1; }
	else
		{ cost10 = cost_binary [ maxA[1]- minA[1]  + 1] + cost_binary[ maxB[0] - minB[0] + 1];}


	//   Find the max cost 
	if ( (cost01 >= cost00) && (cost01 >= cost10) && (cost01>=cost11) )  {r1=0; r2=1;}
	if ( (cost10 >= cost00) && (cost10 >= cost01) && (cost10>=cost11) )  {r1=1; r2=0;}
	if ( (cost00 >= cost01) && (cost00 >= cost10) && (cost00>=cost11) )  {r1=0; r2=0;}
	if ( (cost11 >= cost00) && (cost11 >= cost01) && (cost11>=cost10) )  {r1=1; r2=1;}
	 MIN_A = minA[r1]; MAX_A = maxA[r1];
	 MIN_B = minB[r2]; MAX_B = maxB[r2];

	 // debuging 
//		cerr << "A is in the range: " << MIN_A << " to " << MAX_A << endl;
//		cerr << "B is in the range: " << MIN_B << " to " << MAX_B << endl;

//	printf("queried %d\n",r);
//	printf("returns %d %d\n",r1,r2);
	Answer ret;
	ret.p=r1;
	ret.q=r2;
	return ret;
}

int main()
{
	scanf("%d",&mode);
	if (mode==1){
		scanf("%d%d%d",&N,&A,&B);
		Answer ret=guess(N);
		if (ret.p==A&&ret.q==B){
			printf("CORRECT %d ", N);
		} else printf("WRONG %d ", N);
		printf("%d\n",steps);
	} else {
		scanf("%d",&N);
		MIN_A=0; MIN_B=0;  MAX_A=N-1;  MAX_B=N-1;

		init(); 
		Answer ans = guess(N);
		guessA = ans.p;
		guessB = ans.q;
//		printf("guessed %d %d\n",guessA,guessB);

		if ( (MIN_A  == MAX_A ) && (MIN_B  == MAX_B) && (guessA == MIN_A ) && (guessB == MIN_B)){ 
			printf("CORRECT %d %d\n",N,steps);
		}
		else {
			printf("WRONG %d %d\n",N,steps);
		}
	}
}
