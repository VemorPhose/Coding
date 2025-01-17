import java.util.*;

public class ass7b {
    public static class Shape {
        int getArea () {
            return 0;
        }
    }

    public static class Rectangle extends Shape {
        int length, breadth;
        int getArea () {
            return length * breadth;
        }
    }

    public static void main(String[] args) {
        Rectangle r = new Rectangle();
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter sides of rectangle: ");
        r.length = sc.nextInt();
        r.breadth = sc.nextInt();
        int area = r.getArea();
        System.out.println("Area: " + area);
    }
}
