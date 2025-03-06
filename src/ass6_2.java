// Test JDBC connection
import java.sql.*;

public class ass6_2 {
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
            String qry = "SELECT O_NUM, AMT, ORDER_DATE, C_NUM, S_NUM FROM ORDERS" +
                         " WHERE ORDER_DATE < '2024-01-01'" +
                         " AND AMT > 1500";

            ResultSet rs = stmt.executeQuery(qry);
            
            System.out.println("\nOrder Details:");
            System.out.println("------------------------------------");
            System.out.printf("%-10s %-10s %-20s %-10s %-10s%n", "O_NUM", "AMT", "ORDER_DATE", "C_NUM", "S_NUM");
            System.out.println("------------------------------------");

            while(rs.next()) {
                System.out.printf("%-10s %-10s %-20s %-10s %-10s%n",
                    rs.getString("O_NUM"),
                    rs.getString("AMT"),
                    rs.getString("ORDER_DATE"),
                    rs.getString("C_NUM"),
                    rs.getString("S_NUM")
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