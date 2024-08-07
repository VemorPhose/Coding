import java.util.*;

public class ass0a {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Marks: ");
        int n = sc.nextInt();
        
        if (n >= 90 && n <= 100)
            System.out.println("Grade AA");
        else if (n >= 80 && n <= 90)
            System.out.println("Grade AB");
        else if (n >= 70 && n <= 80)
            System.out.println("Grade BB");
        else if (n >= 0 && n <= 70)
            System.out.println("Grade F");
        else
            System.out.println("Invalid Input!");

        sc.close();
    }
}