#include<bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]){
	char output[100];
	strcpy(output,argv[3]);
	freopen(argv[3],"r",stdin);
	char ans[100];
	map<int,int> m;
	m[1]=1; m[3]=2; m[4]=3; m[5]=4; m[7]=5; m[9]=6; m[13]=7; m[17]=8; m[25]=9; m[33]=10; m[49]=11; m[65]=12; m[97]=13; m[129]=14; m[193]=15; m[257]=16; m[385]=17; m[513]=18; m[769]=19; m[1025]=20; m[1537]=21; m[2049]=22; m[3073]=23; m[4097]=24; m[6145]=25; m[8193]=26; m[10001]=26; 
	int N, S, X;
	scanf("%s %d %d",ans,&N,&S);
	if (strcmp(ans,"CORRECT")==0){
		if (N==12){
			if (S<=6) printf("100\n");
			else if (S<=8) printf("66.66667\n");
			else if (S<12) printf("50\n");
			else printf("0\n");
			printf("Correct answer in %d queries\n",S);
			return 0;
		}
		int prevN=0,prevS=0;
		for (map<int,int>::iterator it=m.begin(); it!=m.end(); ++it){
			int n=it->first, s=it->second;
			if (N>=prevN && N<n){
				X=prevS;
			}
			prevN=n; prevS=s;
		}
		if (N<=2000){
			int diff = S-X;
			if (diff <= 0) printf("100\n");
			else if (diff == 1) printf("83.33333\n");
			else if (diff == 2) printf("66.66667\n");
			else if (diff <= 25) printf("50\n");
			else if (diff < N) printf("33.33333\n");
			else printf("0\n");
			printf("Correct answer in %d queries\n",S);
			return 0;
		}
		int diff = S-X;
		if (diff <= 0) printf("100\n");
		else if (diff == 1) printf("50\n");
		else if (diff == 2) printf("25\n");
		else printf("0\n");
		printf("Correct answer in %d queries\n",S);
	} else {
		printf("0\n");
		printf("Wrong answer\n");
	}
}
