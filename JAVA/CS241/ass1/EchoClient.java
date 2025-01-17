import java.io.*;
import java.net.*;

public class EchoClient {
	public static void main(String[] args) {

		String host = "localhost";
		try {
		    // Creates socket at client end and make connection request to server
			Socket socket = new Socket(host, 8008);
			
			System.out.println("Welcome to Client Program::\n");
			
			// Get input and output stream for the socket
			BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

			for (int i = 1; i <= 5; i++) {
				System.out.println("Sending: line " + i);
				out.println("line" + i);
				out.flush();
			}
			out.println("Over");
			out.flush();

			// receive data from server
			String str = null;
			while ((str = in.readLine()) != null) {
				System.out.println(str);
			}
			in.close();
			out.close();
			socket.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
