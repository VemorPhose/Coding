import java.util.*;

public class ass7a {
    static int add () {
        Scanner sc = new Scanner(System.in);
        int n; System.out.print("number of inputs: ");
        n = sc.nextInt();
        int ret = 0;
        System.out.println("Enter " + n + " numbers");
        for (int i = 0; i < n; i++) {
            int temp = sc.nextInt();
            ret += temp;
        }
        return ret;
    }

    static int add (int a, int b) {
        return a + b;
    }

    static int add (int a, int b, int c) {
        return a + b + c;
    }

    public static void main(String[] args) {
        int a, b, c;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a, b, c: ");
        a = sc.nextInt();
        b = sc.nextInt();
        c = sc.nextInt();

        System.out.println("a + b: " + add(a, b));
        System.out.println("a + b + c: " + add(a, b, c));
        System.out.println("Custom input: ");
        int cust = add();
        System.out.println("Sum: " + cust);

        sc.close();
    }
}
