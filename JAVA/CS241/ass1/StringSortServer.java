import java.io.*;
import java.net.*;
import java.util.Arrays;

public class StringSortServer {
    public static String sortAsc (String str) {
		char[] charArray = str.toCharArray();
		Arrays.sort(charArray);
		return new String(charArray);
	}

	public static String sortDesc (String str) {
		char[] charArray = str.toCharArray();
		Arrays.sort(charArray);
		return new StringBuilder(new String(charArray)).reverse().toString();
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
                    out.println(str + " sorted in ascending order: " + sortAsc(str));
					out.flush();
					out.println(str + " sorted in descending order: " + sortDesc(str));
					out.flush();
				}

				s.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
