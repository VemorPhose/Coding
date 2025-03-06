import java.sql.*;

public class ass6 {
    public static void main(String[] args) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/ass6",
                "root",
                "zxcvbnnm"
            );
            System.out.println("Database connected!\n");

            System.out.println("1: Display Customers sorted by Number and Rating");
            displayCustomersByRating(conn);

            System.out.println("\n2: Display Orders before 2024 with Amount > 1500");
            displayOrdersBefore2024(conn);

            System.out.println("\n3: Update London Salespeople Commission");
            updateLondonCommission(conn);

            System.out.println("\n4: Delete Orders with NULL Amount");
            deleteNullAmountOrders(conn);

            System.out.println("\n5: Display Customers with names starting with 'T'");
            displayCustomersStartingWithT(conn);

            conn.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    private static void displayCustomersByRating(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        String qry = "SELECT C_NUM, C_NAME, RATING FROM CUSTOMERS ORDER BY C_NUM, RATING";
        ResultSet rs = stmt.executeQuery(qry);
        
        System.out.println("Customer Details:");
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
    }

    private static void displayOrdersBefore2024(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        String qry = "SELECT O_NUM, AMT, ORDER_DATE, C_NUM, S_NUM FROM ORDERS " +
                    "WHERE ORDER_DATE < '2024-01-01' AND AMT > 1500";
        ResultSet rs = stmt.executeQuery(qry);
        
        System.out.println("Order Details:");
        System.out.println("------------------------------------");
        System.out.printf("%-10s %-10s %-20s %-10s %-10s%n", 
                        "O_NUM", "AMT", "ORDER_DATE", "C_NUM", "S_NUM");
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
    }

    private static void updateLondonCommission(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        String qry = "UPDATE SALES_PEOPLE SET COMM = 0.25 WHERE CITY = 'London'";
        int rowsAffected = stmt.executeUpdate(qry);
        System.out.println(rowsAffected + " salespeople updated.\n");

        qry = "SELECT S_NUM, S_NAME, CITY, COMM FROM SALES_PEOPLE";
        ResultSet rs = stmt.executeQuery(qry);
        
        System.out.println("Sales People Details:");
        System.out.println("------------------------------------");
        System.out.printf("%-10s %-20s %-20s %-10s%n", "S_NUM", "S_NAME", "CITY", "COMM");
        System.out.println("------------------------------------");

        while(rs.next()) {
            System.out.printf("%-10s %-20s %-20s %-10s%n",
                rs.getString("S_NUM"),
                rs.getString("S_NAME"),
                rs.getString("CITY"),
                rs.getString("COMM")
            );
        }
        rs.close();
        stmt.close();
    }

    private static void deleteNullAmountOrders(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        String qry = "DELETE FROM ORDERS WHERE AMT IS NULL";
        int rowsAffected = stmt.executeUpdate(qry);
        System.out.println(rowsAffected + " orders deleted.\n");

        qry = "SELECT O_NUM, AMT, ORDER_DATE, C_NUM, S_NUM FROM ORDERS ";
        ResultSet rs = stmt.executeQuery(qry);
        
        System.out.println("Order Details:");
        System.out.println("------------------------------------");
        System.out.printf("%-10s %-10s %-20s %-10s %-10s%n", 
                        "O_NUM", "AMT", "ORDER_DATE", "C_NUM", "S_NUM");
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
    }

    private static void displayCustomersStartingWithT(Connection conn) throws SQLException {
        Statement stmt = conn.createStatement();
        String qry = "SELECT C_NUM, C_NAME FROM CUSTOMERS WHERE C_NAME LIKE 'T%'";
        ResultSet rs = stmt.executeQuery(qry);
        
        System.out.println("Customer Details:");
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
    }
}
