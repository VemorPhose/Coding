import java.util.*;

public class ass0b {
    public static void main(String[] args) {
        int[] arr = new int[10];
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter 10 integers: ");
        for (int i = 0; i < 10; i++) {
            arr[i] = sc.nextInt();
        }
        int max = Integer.MIN_VALUE, smax = Integer.MIN_VALUE;
        for (int i = 0; i < 10; i++) {
            if (arr[i] > max) {
                smax = max;
                max = arr[i];
            }
            else if (arr[i] > smax) {
                smax = arr[i];
            }
        }

        System.out.println("Second max element in the array is: " + smax);
        sc.close();
    }
}
