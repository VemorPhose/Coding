import java.io.*;
import java.net.*;

public class PalindromeServer {
    public static boolean isPalindrome (String str) {
        int len = str.length();
        for (int i = 0; i < len / 2; i++) {
            if (str.charAt(i)!= str.charAt(len - i - 1))
                return false;
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
                    boolean isPal = isPalindrome(str);
                    if (isPal == true) out.println(str + " is a Palindrome.");
                    else out.println(str + " is not a Palindrome.");
					out.flush();
				}

				s.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
