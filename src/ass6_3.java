// Test JDBC connection
import java.sql.*;

public class ass6_3 {
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
            String qry = "UPDATE SALES_PEOPLE " +
                            "SET COMM = 0.25 " +
                            "WHERE CITY = 'London'";

            int rowsAffected = stmt.executeUpdate(qry);
            System.out.println(rowsAffected + " salespeople updated.\n");


            stmt.close();
            conn.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}