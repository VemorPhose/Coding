import java.io.*;
import java.net.*;
import java.util.*;

public class PrimeClient {
    public static void main(String[] args) {
        String host = "localhost";
        try {
            Socket socket = new Socket(host, 8008);

            System.out.println("Welcome to Client Program::\n");

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

            System.out.print("Enter number: ");
            Scanner sc = new Scanner(System.in);
            String ooga = sc.next();
            System.out.println("Sending: " + ooga);
            out.println(ooga);
            out.flush();

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
            sc.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
