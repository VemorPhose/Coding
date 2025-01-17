import java.io.*;
import java.net.*;

public class PrimeServer {
    public static boolean isPrime(String str) {
        int num = Integer.parseInt(str);
        if (num <= 1) return false;
        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) return false;
        }
        return true;
    }
	public static void main(String[] args) {
		try {
		
			ServerSocket server = new ServerSocket(8008);
			boolean flag = true;
			System.out.println("Welcome to Server Program::\n");
			
			while (flag) {
				Socket s = server.accept();
				
				BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
				PrintWriter out = new PrintWriter(new OutputStreamWriter(s.getOutputStream()));

				out.print("Hello! This is the Java Server. ");
				out.println("Enter 'Over' to exit.");
				out.flush();
				String str = null;
				while ((str = in.readLine()) != null) {
					System.out.println("Received: " + str);
                    if (str.equals("Over")) {
						flag = false;
						break;
					}
                    boolean prime = isPrime(str);
                    if (prime == true) out.println(str + " is a Prime Number.");
                    else out.println(str + " is not a Prime Number.");
					out.flush();
				}

				s.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
