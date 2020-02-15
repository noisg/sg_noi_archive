import java.util.Scanner;
class VisitingSingapore {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int k = input.nextInt();
    int n= input.nextInt();
    int m = input.nextInt();
    long x = input.nextInt();
    long y = input.nextInt();
    x = -x;
    y = -y;
    long ans = -x-y*m;
    long val[] = new long[k + 1]; 
    for (int i = 0; i < k; i++) {
      val[i+1] = input.nextInt();
    } 
    int arr[] = new int[n + 1];
    int arr2[] = new int[m + 1];
    for (int i = 1; i <= n; i++) {
      arr[i] = input.nextInt();
    } 
    for (int i = 1; i <= m; i++) {
      arr2[i] = input.nextInt();
    }
    long dp[][][] = new long[2][m+2][4];
    long lower = -2000000000;
    for(int i=1;i<=m;i++){
		dp[0][i][0] = lower;
		dp[0][i][1] = lower;
		dp[0][i][3] = lower;
		dp[0][i][2] = -x-y*i;
	}
	dp[0][0][0] = lower;
	dp[0][0][1] = lower;
	dp[0][0][2] = lower;
	dp[0][0][3] = 0;
	dp[1][0][0] = lower;
	dp[1][0][1] = lower;
	dp[1][0][2] = lower;
	dp[1][0][3] = 0;
    for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i%2][j][0] = Math.max(-x-y*j,Math.max(Math.max(dp[i%2][j-1][0],dp[(i-1)%2][j][0])-y,Math.max(dp[(i-1)%2][j][2],dp[i%2][j-1][1])-x-y));
			dp[i%2][j][1] = Math.max(dp[(i-1)%2][j][1]-y,dp[(i-1)%2][j][3]-x-y);
			dp[i%2][j][2] = Math.max(Math.max(dp[i%2][j-1][2]-y,dp[i%2][j-1][3]-x-y),-x-y*j);
			if(arr[i]==arr2[j]){
				dp[i%2][j][3] = (long)val[arr[i]]+Math.max(Math.max(dp[(i-1)%2][j-1][0],dp[(i-1)%2][j-1][1]),Math.max((long)dp[(i-1)%2][j-1][2],(long)dp[(i-1)%2][j-1][3]));
			}else dp[i%2][j][3] = lower;
//			cout<<i<<" "<<j<<" states: \n";
//			for(k=0;k<4;k++)cout<<dp[i][j][k]<<" "<<k/2<<k%2<<'\n';
		}
		for(int j=0;j<4;j++)ans = Math.max(ans,dp[i%2][m][j]);
	}
    System.out.println(ans);
  }
}