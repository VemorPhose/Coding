import java.util.*;

public class ass12b {
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

    public static void main(String[] args) throws InterruptedException {
        Scanner scanner = new Scanner(System.in);
        cnt = scanner.nextInt();

        Thread t1 = new Thread(new CounterIncrementer());
        Thread t2 = new Thread(new CounterDecrementer());

        System.out.println("Start Value: " + cnt);
        t1.start();
        
        try {
            t1.join();
        } catch (InterruptedException e) {
            System.out.println("Exception Caught: " + e);
        }
        
        System.out.println("t1 Finished: " + cnt);
        t2.start();
        
        try {
            t2.join();
        } catch (InterruptedException e) {
            System.out.println("Exception Caught: " + e);
        }

        System.out.println("t2 Finished: " + cnt);
        
        scanner.close();
    }
}
