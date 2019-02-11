#include <bits/stdc++.h>
using namespace std;

FILE *input;
FILE *output;
FILE *testOutput;

#define INF 1000000000

void quit(int score){
    printf("%.2lf\n",(double)score/100);
    exit(0);
}
void quit(int score,string str){
    printf("%.2lf\n",(double)score/100);
    fprintf(stderr, "%s\n",str.c_str());
    exit(0);
}

int n,m;
vector<int> X,A,B,C;

int main(int argc, char **argv){
    input = fopen(argv[1], "r");
    //output = fopen(argv[2], "r");
    testOutput = fopen(argv[3], "r");
    fscanf(input,"%d%d",&n,&m);
    X.resize(n);
    A.resize(m);
    B.resize(m);
    C.resize(m);
    for(int i=0;i<m;i++){
        fscanf(input,"%d%d%d",&A[i],&B[i],&C[i]);
    }
    for(int i=0;i<n;i++){
        if(fscanf(testOutput,"%d",&X[i])!=1)quit(0, "Output isn't correct");
        if(X[i]<1 || X[i]>INF)quit(0, "Output isn't correct");
    }
    for(int i=0;i<m;i++){
        if(min(X[A[i]-1],X[B[i]-1])!=C[i])quit(0, "Output isn't correct");
    }
    quit(100, "Output is correct");
}

