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
long long solve(int n, vector<long long> T){
	deque<tp> convexHull; //intersect, gradient, constant
	long long curMax = 0, curDpVal = 0;
	for(int i = 1; i <= n; i++){
		long long curT = T[i];
		if(curT >= curMax){
			long long grad = -i+1, constant = curDpVal;
			while(convexHull.size() >= 2 && cmp(convexHull[convexHull.size()-2],convexHull.back(),grad,constant)){
				convexHull.pop_back();
			}
			tp newLine = make_tuple(2e9,grad,constant);
			if(i!=1)get<0>(convexHull.back()) = intersect(convexHull.back(),newLine);
			convexHull.push_back(newLine);
			curMax = curT;
			while(get<0>(convexHull.front())<(long double)curMax)convexHull.pop_front();
			long double temp;
			tie(temp, grad, constant) = convexHull.front();
			curDpVal = n*curMax + grad * curMax + constant;
		}
	}
	return curDpVal;
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

int main(){
	int n;
	n = readInt();
	vector<long long> T(n+1);
	for(int i = 1; i <= n; i++) T[i] = readInt();
	long long answer = solve(n, T);
	cout << answer;
}
