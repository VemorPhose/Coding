// Test JDBC connection
import java.sql.*;

public class ass6_5 {
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/ass6",
                "root",
                "zxcvbnnm"
            );
            System.out.println("Database connected!\n");

            Statement stmt = conn.createStatement();
            String qry = "SELECT C_NUM, C_NAME FROM CUSTOMERS" +
                         " WHERE C_NAME LIKE 'T%'";

            ResultSet rs = stmt.executeQuery(qry);
            
            System.out.println("\nCustomer Details:");
            System.out.println("------------------------------------");
            System.out.printf("%-10s %-20s%n", "C_NUM", "C_NAME");
            System.out.println("------------------------------------");

            while(rs.next()) {
                System.out.printf("%-10s %-20s%n",
                    rs.getString("C_NUM"),
                    rs.getString("C_NAME")
                );
            }

            rs.close();
            stmt.close();
            conn.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}