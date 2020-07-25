#include<bits/stdc++.h>
using namespace std;
typedef tuple<long double, long long,long long>  tp;
bool cmp(tp T1, tp T2, long long grad, long long constant){
	long double m1, c1, m2, c2;
	long double temp;
	tie(temp,m1,c1) = T1;
	tie(temp,m2,c2) = T2;
	return (constant - c2)*(m1 - grad) < (constant - c1)*(m2 - grad);
}
long double intersect(tp T1, tp T2){
	long double m1, c1, m2, c2;
	long double temp;
	tie(temp,m1,c1) = T1;
	tie(temp,m2,c2) = T2;
	return (long double)(c1-c2)/(long double)(m2-m1);
}
inline long long readInt() {
    long long x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
    return x;
}
long long solve(int n, vector<long long> T){
	vector<long long> dp;
	deque<tp> convexHull; //intersect, gradient, constant
	long long curMax = 0;
	dp.push_back(0);
	convexHull.push_back(make_tuple(2e9,0ll,0ll));
	long long curDpVal;
	for(int i = 1; i <= n; i++){
		long long curT = T[i];
		if(curT >= curMax){
			curMax = curT;
			while(get<0>(convexHull.front())<(long double)curMax)convexHull.pop_front();
			long double temp;
			long long grad,constant;
			tie(temp, grad, constant) = convexHull.front();
			curDpVal = n*curMax + grad * curMax + constant;
		}
		dp.push_back(curDpVal);
		long long grad = -i;
		long long constant = dp[i];
		while(convexHull.size() >= 2 && cmp(convexHull[convexHull.size()-2],convexHull.back(),grad,constant)){
			convexHull.pop_back();
		}
		tp newLine = make_tuple(2e9,grad,constant);
		get<0>(convexHull.back()) = intersect(convexHull.back(),newLine);
		convexHull.push_back(newLine);
	}
	return dp[n];
}

int main(){
	int n;
	n = readInt();
	vector<long long> T(n+1);
	for(int i = 1; i <= n; i++) T[i]=readInt();
	long long answer = solve(n, T);
	cout << answer;
}
