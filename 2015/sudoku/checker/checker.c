#include <stdio.h>
#include <stdlib.h>

static char* ch;
FILE *inp, *outp, *uoutp;
void quit(er)
char* er;
{
	printf("0\n%s\n",er);
	exit(0);
}

void getsudoku(sudoku)
int sudoku[];
  { int a;
    for (a=0;a<81;a++)
      { if (fscanf(uoutp, "%d", &sudoku[a]) == 1) {
			if (sudoku[a] < 0 || sudoku[a] > 9) quit("Invalid Sudoku");
		}
		else quit("Invalid Sudoku");  }
    return; }

void rowinit(sudoku,a,b)
int sudoku[]; int a,b;
  { int c;
    for (c=0;c<9;c++)
      { sudoku[a+((b+c)%9)] = (c+1); }
    return; }

void init(sudoku)
int sudoku[];
  { rowinit(sudoku, 0,0);
    rowinit(sudoku, 9,3);
    rowinit(sudoku,18,6);
    rowinit(sudoku,27,1);
    rowinit(sudoku,36,4);
    rowinit(sudoku,45,7);
    rowinit(sudoku,54,2);
    rowinit(sudoku,63,5);
    rowinit(sudoku,72,8);
    return; }

void printsudoku(sudoku)
int sudoku[];
  { int a;
    printf("\nCurrent Sudoku\n \n");
    for (a=0;a<81;a+=9)
      { printf(" %d %d %d  %d %d %d  %d %d %d \n",
        sudoku[a+0],sudoku[a+1],sudoku[a+2],
        sudoku[a+3],sudoku[a+4],sudoku[a+5],
        sudoku[a+6],sudoku[a+7],sudoku[a+8]);
        if ((a==18)||(a==45)||(a==72)) { putchar('\n'); } }
    return; }

int inrow(sudoku,a)
int sudoku[]; int a;
  { int b;
    b = (1 << sudoku[a+ 0])|
        (1 << sudoku[a+ 1])|
        (1 << sudoku[a+ 2])|
        (1 << sudoku[a+ 3])|
        (1 << sudoku[a+ 4])|
        (1 << sudoku[a+ 5])|
        (1 << sudoku[a+ 6])|
        (1 << sudoku[a+ 7])|
        (1 << sudoku[a+ 8]);
    return(b & 1022); }

int incolumn(sudoku,a)
int sudoku[]; int a;
  { int b;
    b = (1 << sudoku[a+ 0])|
        (1 << sudoku[a+ 9])|
        (1 << sudoku[a+18])|
        (1 << sudoku[a+27])|
        (1 << sudoku[a+36])|
        (1 << sudoku[a+45])|
        (1 << sudoku[a+54])|
        (1 << sudoku[a+63])|
        (1 << sudoku[a+72]);
    return(b & 1022); }

int inquadrant(sudoku,a)
int sudoku[]; int a;
  { int b;
    b = (1 << sudoku[a+ 0])|
        (1 << sudoku[a+ 1])|
        (1 << sudoku[a+ 2])|
        (1 << sudoku[a+ 9])|
        (1 << sudoku[a+10])|
        (1 << sudoku[a+11])|
        (1 << sudoku[a+18])|
        (1 << sudoku[a+19])|
        (1 << sudoku[a+20]);
    return(b & 1022); }

int checkrow(sudoku,a)
int sudoku[]; int a;
  { int b;
    b = (1 << sudoku[a+ 0])|
        (1 << sudoku[a+ 1])|
        (1 << sudoku[a+ 2])|
        (1 << sudoku[a+ 3])|
        (1 << sudoku[a+ 4])|
        (1 << sudoku[a+ 5])|
        (1 << sudoku[a+ 6])|
        (1 << sudoku[a+ 7])|
        (1 << sudoku[a+ 8]);
    if (b == 1022) { return(1); } else { return(0); } }

int checkcolumn(sudoku,a)
int sudoku[]; int a;
  { int b;
    b = (1 << sudoku[a+ 0])|
        (1 << sudoku[a+ 9])|
        (1 << sudoku[a+18])|
        (1 << sudoku[a+27])|
        (1 << sudoku[a+36])|
        (1 << sudoku[a+45])|
        (1 << sudoku[a+54])|
        (1 << sudoku[a+63])|
        (1 << sudoku[a+72]);
    if (b == 1022) { return(1); } else { return(0); } }

int checkquadrant(sudoku,a)
int sudoku[]; int a;
  { int b;
    b = (1 << sudoku[a+ 0])|
        (1 << sudoku[a+ 1])|
        (1 << sudoku[a+ 2])|
        (1 << sudoku[a+ 9])|
        (1 << sudoku[a+10])|
        (1 << sudoku[a+11])|
        (1 << sudoku[a+18])|
        (1 << sudoku[a+19])|
        (1 << sudoku[a+20]);
    if (b == 1022) { return(1); } else { return(0); } }

int checksudoku(sudoku)
int sudoku[];
  { return(checkrow(sudoku, 0) &
           checkrow(sudoku, 9) &
           checkrow(sudoku,18) &
           checkrow(sudoku,27) &
           checkrow(sudoku,36) &
           checkrow(sudoku,45) &
           checkrow(sudoku,54) &
           checkrow(sudoku,63) &
           checkrow(sudoku,72) &
           checkcolumn(sudoku,0) &
           checkcolumn(sudoku,1) &
           checkcolumn(sudoku,2) &
           checkcolumn(sudoku,3) &
           checkcolumn(sudoku,4) &
           checkcolumn(sudoku,5) &
           checkcolumn(sudoku,6) &
           checkcolumn(sudoku,7) &
           checkcolumn(sudoku,8) &
           checkquadrant(sudoku, 0) &
           checkquadrant(sudoku, 3) &
           checkquadrant(sudoku, 6) &
           checkquadrant(sudoku,27) &
           checkquadrant(sudoku,30) &
           checkquadrant(sudoku,33) &
           checkquadrant(sudoku,54) &
           checkquadrant(sudoku,57) &
           checkquadrant(sudoku,60)); }

int columnexchange(sudoku,a,b)
int sudoku[]; int a,b;
  { if (quadrant(a) != quadrant(b)) { return(0); }
    int c; int d;
    for (c=0;c<81;c+=9)
      { d = sudoku[c+a]; sudoku[c+a] = sudoku[c+b]; sudoku[c+b] = d; }
    return(1); }

int rowexchange(sudoku,a,b)
int sudoku[]; int a,b;
  { if (quadrant(a) != quadrant(b)) { return(0); }
    int c; int d;
    for (c=0;c<9;c++)
      { d = sudoku[c+a]; sudoku[c+a] = sudoku[c+b]; sudoku[c+b] = d; }
    return(1); }

int row(a)
int a;
  { return(9*(a/9)); }

int column(a)
int a;
  { return(a%9); }

int quadrant(a)
int a;
  { return((a/27)*27+(((a%9)/3)*3)); }

int moveable(sudoku,a)
int sudoku[]; int a;
  { if (sudoku[a] != 0) { return(0); }
    int b = row(a); int c = column(a); int d = quadrant(a);
    int e = inrow(sudoku,b) | incolumn(sudoku,c) | inquadrant(sudoku,d);
    int j = 0; int i;
    for (i=1;i<=9;i++)
      { if (((e & (1 << i)) == 0) && (j == 0)) { j = i; }
        else if (((e & (1 << i)) == 0) && (j > 0)) { return(0); } }
    return(j); }

int suberase(sudoku,d,e)
int sudoku[]; int d; int e;
  { int a = e; int b; int c = 0;
    if (d%3==0) { return(0); }
    while (c < 85)
      { if (sudoku[a] > 0)
          { b = sudoku[a]; sudoku[a] = 0;
            if (moveable(sudoku,a) == b) 
              { c = 0; }
            else { sudoku[a] = b; c++; } }
        a = (a+d)%81; }
    c=0; for (a=0;a<81;a++)
      { if (sudoku[a]==0) { c++; } }
    return(c); }

int erase(sudoku)
int sudoku[];
  { int sudokv[81]; int sudokw[81];  int a; int b; int c = 0; int d; int e;
    for (e=0;e<81;e++) { for (d=1;d<81;d++)
      { for (a=0;a<81;a++) { sudokv[a] = sudoku[a]; }
        b = suberase(sudokv,d,e);
        if (b>c)
          { c = b;
            for (a=0;a<81;a++) { sudokw[a] = sudokv[a]; } } } }
    for (a=0;a<81;a++) { sudoku[a] = sudokw[a]; }
    return(c); }     

void solve(sudoku)
int sudoku[];
  { int a = 0; int c = 0; int b;
    while (c < 85)
      { if (sudoku[a] == 0)
          { b = moveable(sudoku,a);
            if (b > 0)
              { sudoku[a] = b; c = 0; } }
        a = (a+1)%81; c++; }
    return; }
int condread(condarray)
int condarray[];
  { int a; int b; int x;
    for (b=0;b<9;b++) { condarray[b]=81; }
    b = 0;
    for (a=0;a<81;a++)
      {
		  fscanf(inp, "%d", &x);
		  if (x == 1)
          { if (b>8) { return(10); }
            condarray[b]=a; b++; } }
    return(b); }  

int adjust(sudoku)
int sudoku[];
  { int condarray[10]; int a,b,c,i,j,k;
    b = condread(condarray);
    if (b > 9) { return(0); }
    for (c=0;c<b;c++)
      { i = row(condarray[c]); j = column(condarray[c]);
        k = quadrant(condarray[c]);
        /* printf("Condition %d %d %d %d \n",condarray[c],i,j,k); */
        a = k;
        if (sudoku[a] != 1) { a = k+1; }
        if (sudoku[a] != 1) { a = k+2; }
        if (sudoku[a] != 1) { a = k+9; }
        if (sudoku[a] != 1) { a = k+10; }
        if (sudoku[a] != 1) { a = k+11; }
        if (sudoku[a] != 1) { a = k+18; }
        if (sudoku[a] != 1) { a = k+19; }
        if (sudoku[a] != 1) { a = k+20; }
        if (sudoku[a] != 1) { printf("Sudoku invalid.\n"); return(0); 
        printf("Position %d %d %d %d \n",a,row(a),column(a),quadrant(a)); }
        if (row(a) != i)
          { if (rowexchange(sudoku,row(a),i) == 0) { return(0); } }
        if (column(a) != j)
          { if (columnexchange(sudoku,column(a),j) == 0) { return(0); } } }
    for (c=0;c<b;c++)
      { if (sudoku[condarray[c]]!=1) { return(0); } }
    return(1); }

int main(int argc, char **argv)
  { int sudoku[81]; int c; int e;
	inp = fopen(argv[1], "r");
	outp = fopen(argv[2], "r");
	uoutp = fopen(argv[3], "r");
    
    int condarray[10]; int d;
    //fscanf(inp, "%d", &d);
    
    condread(condarray);
    getsudoku(sudoku);
    int a; c = 0;
    for (a=0;a<81;a++)
      { if (sudoku[a] == 0) { c++; } }
    solve(sudoku);
    if (checksudoku(sudoku) != 1) quit("Sudoku Not Human Solvable");
    
    //if (c < d) { e = 0; }
    for (a=0;a<9;a++)
      { if ((condarray[a]<81)&&(sudoku[condarray[a]]!=1)) {  
		  quit("Sudoku does not satisfy the restrictions!"); 
		 } }
	if (c >= 51) printf("100\n");
    else printf("%d\n", (int) (3 + c/3)*5 ); 
	printf("%d free fields.\n", c);
    return 0; }
 
