#include <stdio.h>

long numbread()
  { char ch; long b;
    ch = ' ';
    while ((ch < '0') || (ch > '9'))
      { ch = getchar(); }
    b = 0;
    while ((ch >= '0') && (ch <= '9'))
      { b = b*10+(long)(ch-'0'); ch = getchar(); }
    return(b); }


void arrayadd(long i, long j, long k, long m, long n, long a[])
  { long x = m*i; long y = m*j; long p; long q; long v; long w;
    for (p=0;p<m-k;p++)
      { if (i > 0) { v = a[x+p]; } else
          { if (p==0) { v = 1; } else { v = 0; } }
        for (q=p+k;q<m;q++)
          { w = v+a[y+q];
            if (w > 500000000) { w = 500000001; }
            a[y+q] = w; } } }

main()
  {
  long n = numbread(); long m = numbread(); long h = numbread();
  long i,j,k,o;
  long consty = n*m;
  long a[consty];
  for (o=0;o<n*m;o++)
    { a[o] = 0; }
  for (i=0;i<n-1;i++)
    { for (o=0;o<h;o++)
        { j = numbread(); k = numbread();
          if ((i<j) && (j<n))
            { arrayadd(i,j,k,m,n,a); } } }
  for (o=n*m-m; o<n*m; o++)
    { printf("%ld ",a[o]); }
  putchar('\n');
  }
