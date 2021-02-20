import java.util.*;
import java.util.Arrays;

public class Competition {
	public static void main (String[] args) {
		Scanner cin = new Scanner(System.in);
		int n = cin.nextInt();
		int a = cin.nextInt();
		int b = cin.nextInt();
		int[] A = new int[n];
		int ans=0;
		for(int i=0;i<n;i++){
			A[i]=cin.nextInt();
			ans+=A[i];
		}
		for(int i=0;i<n;i++){
			A[i] = cin.nextInt() - A[i];
		}
		Arrays.sort(A);
		for(int i=n-1;i>=n-b;i--){
			ans+=A[i];
		}
		System.out.println(ans);
		return;
	}
}