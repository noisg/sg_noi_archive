#include <stdio.h>
#include <stdlib.h>

long numbread(FILE *fily)
  { char ch; long b;
    ch = ' ';
    while ((ch < '0') || (ch > '9'))
      { ch = fgetc(fily); }
    b = 0;
    while ((ch >= '0') && (ch <= '9'))
      { b = b*10+(long)(ch-'0'); ch = getc(fily); }
    return(b); }

void numbwrite(FILE *fily,long a, char b)
  { fprintf(fily,"%ld%c",a,b); }

/**
Mandatory Inputs:
- Randomseed
  (A randomseed below 20 gives a two-stop matrix;
   an even randomseed does not have flights in wrong direction,
   a randomseed of 7 mod 14 with n proper multiple of h 
   gives no double destinations but backward flights);
- Number n of cities;
- Number m of nights;
- Number k of maximum mandatory nights per stop-over;
- Number h of outgoing flights per city.
**/

void matrixmake(char *inputfilename, long c,long n, long m, long k, long h)
  { srand((unsigned int)(c));
    long i; long j; long l;
    FILE *inputfile;
    inputfile = fopen(inputfilename,"w");
    numbwrite(inputfile,n,' '); numbwrite(inputfile,m,' ');
    numbwrite(inputfile,h,'\n');
    for (i = 0; i < n-1; i++)
      { for (j= 0; j < h-1; j++)
          { if (c < 20) { if ((i==0)&&(j<n-1)) { numbwrite(inputfile,j+1,' '); }
                          else { numbwrite(inputfile,n-1,' '); } }
            else if (c%2 == 0)
              { numbwrite(inputfile,i+1+(rand() % (n-i-1)),' '); }
            else if ((c%14 == 7)&& (n%h == 0) && (h<n))
              { numbwrite(inputfile,j*(n/h)+(rand()%(n/h)),' '); }
            else { numbwrite(inputfile,rand() % n,' '); }
            numbwrite(inputfile,rand() % k,' '); }
        numbwrite(inputfile,n-1,' '); numbwrite(inputfile,0,'\n'); }
  fclose(inputfile); }

void arrayadd(long i, long j, long k, long m, long n, long a[])
  { long x = m*i; long y = m*j; long p; long q; long v; long w;
    for (p=0;p<m-k;p++)
      { if (i > 0) { v = a[x+p]; } else
          { if (p==0) { v = 1; } else { v = 0; } }
        for (q=p+k;q<m;q++)
          { w = v+a[y+q];
            if (w > 500000000) { w = 500000001; }
            a[y+q] = w; } } }

void journey(char *inputfilename, char *outputfilename)
  { FILE *inputfile; FILE *outputfile;
  inputfile = fopen(inputfilename,"r");
  outputfile = fopen(outputfilename,"w");
  long n = numbread(inputfile);
  long m = numbread(inputfile);
  long h = numbread(inputfile);
  long i,j,k,o;
  long consty = n*m;
  long a[consty];
  for (o=0;o<n*m;o++)
    { a[o] = 0; }
  for (i=0;i<n-1;i++)
    { for (o=0;o<h;o++)
        { j = numbread(inputfile); k = numbread(inputfile);
          if ((i<j) && (j<n))
            { arrayadd(i,j,k,m,n,a); } } }
  for (o=n*m-m; o<n*m; o++)
    { fprintf(outputfile,"%ld ",a[o]); }
  fprintf(outputfile,"\n");
  fclose(inputfile); fclose(outputfile);
  }

main()
  {
  matrixmake("journeydata/1-1.in",2,9,9,1,8);
  journey("journeydata/1-1.in","journeydata/1-1.out");
  matrixmake("journeydata/1-2.in",2,8,8,1,8);
  journey("journeydata/1-2.in","journeydata/1-2.out");
  matrixmake("journeydata/2-1.in",133,18,8,1,9);
  journey("journeydata/2-1.in","journeydata/2-1.out");
  matrixmake("journeydata/2-2.in",147,18,8,1,9);
  journey("journeydata/2-2.in","journeydata/2-2.out");
  matrixmake("journeydata/3-1.in",228,99,99,9,19);
  journey("journeydata/3-1.in","journeydata/3-1.out");
  matrixmake("journeydata/3-2.in",328,99,99,9,19);
  journey("journeydata/3-2.in","journeydata/3-2.out");
  matrixmake("journeydata/4-1.in",557,10000,25,10,25);
  journey("journeydata/4-1.in","journeydata/4-1.out");
  matrixmake("journeydata/4-2.in",5557,6000,150,125,25);
  journey("journeydata/4-2.in","journeydata/4-2.out");
  matrixmake("journeydata/4-3.in",257,800,400,100,25);
  journey("journeydata/4-3.in","journeydata/4-3.out");
  }
