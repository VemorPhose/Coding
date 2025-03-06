// Test JDBC connection
import java.sql.*;

public class ass6_4 {
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
            String qry = "DELETE FROM ORDERS WHERE AMT IS NULL";

            int rowsAffected = stmt.executeUpdate(qry);
            System.out.println(rowsAffected + " orders deleted.\n");

            stmt.close();
            conn.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}