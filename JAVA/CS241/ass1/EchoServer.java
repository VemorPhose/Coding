import java.io.*;
import java.net.*;

public class EchoServer {
	public static void main(String[] args) {
		try {
		
			// Creates Server Socket object 
			ServerSocket server = new ServerSocket(8008);
			boolean flag = true;
			System.out.println("Welcome to Server Program::\n");
			
			// Infinitely wait for client 
			while (flag) {
				Socket s = server.accept();
				
				// Get input and output stream for the socket
				BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
				PrintWriter out = new PrintWriter(new OutputStreamWriter(s.getOutputStream()));

				out.print("Hello! This is the Java EchoServer. ");
				out.println("Enter 'Over' to exit.");
				out.flush();
				String str = null;
				while ((str = in.readLine()) != null) {
					System.out.println("Received: " + str);
					out.println("Echo: " + str);
					out.flush();
					if (str.equals("Over")) {
						flag = false;
						break;
					}
				}

				s.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
