import java.util.*;

public class ass12d {
    public static int cnt = 0;

    public static class CounterIncrementer extends Thread {
        public void run() {
            cnt += 5000;
            System.out.println("Inside Incrementer: " + cnt);
        }
    }

    public static class CounterDecrementer extends Thread {
        public void run() {
            cnt -= 3000;
            System.out.println("Inside Decrementer: " + cnt);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Scanner scanner = new Scanner(System.in);
        cnt = scanner.nextInt();

        CounterIncrementer t1 = new CounterIncrementer();
        CounterDecrementer t2 = new CounterDecrementer();

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