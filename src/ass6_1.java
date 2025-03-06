// Test JDBC connection
import java.sql.*;

public class ass6_1 {
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
            String qry = "SELECT C_NUM, C_NAME, RATING FROM CUSTOMERS" +
                         " ORDER BY C_NUM, RATING";

            ResultSet rs = stmt.executeQuery(qry);
            
            System.out.println("\nCustomer Details:");
            System.out.println("------------------------------------");
            System.out.printf("%-10s %-20s %-10s%n", "C_NUM", "C_NAME", "RATING");
            System.out.println("------------------------------------");

            while(rs.next()) {
                System.out.printf("%-10s %-20s %-10s%n",
                    rs.getString("C_NUM"),
                    rs.getString("C_NAME"),
                    rs.getString("RATING")
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