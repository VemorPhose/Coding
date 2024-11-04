import java.util.*;

public class ass12a {
    public static int cnt = 0;

    public static class CounterIncrementer implements Runnable {
        public void run() {
            cnt += 5000;
            System.out.println("Inside Incrementer: " + cnt);
        }
    }

    public static class CounterDecrementer implements Runnable {
        public void run() {
            cnt -= 3000;
            System.out.println("Inside Decrementer: " + cnt);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        cnt = scanner.nextInt();

        Thread t1 = new Thread(new CounterIncrementer());
        Thread t2 = new Thread(new CounterDecrementer());

        System.out.println("Start Value: " + cnt);
        t1.start();
        System.out.println("t1 Finished: " + cnt);
        t2.start();
        System.out.println("t2 Finished: " + cnt);

        scanner.close();
    }
}
