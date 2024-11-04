import java.util.*;

class Hello {
    void m1() {
        System.out.print("H1");
    }

    void m2() {
        System.out.print("H2");
        m1();
    }
}

class Test10 extends Hello {
    void m1() {
        System.out.print("T1");
    }
}

public class b {
    public static void main(String[] args) {
        Test10 t = new Test10();
        t.m2(); // Calls m2() from Test10, which calls m1() from Test10

        Hello h1 = new Hello();
        h1.m2(); // Calls m2() from Hello, which calls m1() from Hello
    }
}