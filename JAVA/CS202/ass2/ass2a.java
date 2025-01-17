import java.util.*;

public class ass2a {
	public static void main (String[] args) {
		int m, n;
		System.out.println("enter size of arrays space separated: ");
		Scanner sc = new Scanner(System.in);
		m = sc.nextInt();
		n = sc.nextInt();
		int[] arr = new int[m];
		int[] brr = new int[n];

		System.out.println("enter elements of array 1 and 2 in order: ");
		for (int i = 0; i < m; i++) 
			arr[i] = sc.nextInt();
		for (int i = 0; i < n; i++) 
			brr[i] = sc.nextInt();
		sc.close();
	
		int[] crr = new int[m+n];
		int i = 0, j = 0;
		while (i < m || j < n) {
			if (i==m) {crr[i+j] = brr[j]; j++;}
			else if (j==n) {crr[i+j] = arr[i]; i++;}
			else {
				if (arr[i] < brr[j]) {crr[i+j] = arr[i]; i++;}
				else {crr[i+j] = brr[j]; j++;}
			}
		}

		System.out.print("arr3[] = {");
		for (int k = 0; k < m+n-1; k++) System.out.print(crr[k] + ", ");
		System.out.print(crr[m+n-1] + "}\n");
	}
}	
		