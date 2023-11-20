import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;


// Connection
// Statement
// DriverManager.con();
// con.createStatement();
// smt.executeUpdate(string)
// ResultSet
//  ResultSetMetaData rsmd = resultSet.getMetaData();
public class DatabaseConnectivity
{

    public static void main(String args[]) {
        System.out.println("1. Check Connection");
        System.out.println("Enter choice: ");
        Scanner sc1 = new Scanner(System.in);
        int ch = sc1.nextInt();
        Connection con = null;
        Statement smt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://10.10.13.128/31252_db", "te31252", "te31252");
            // "jdbc:mysql://localhost or 127... (port)(10.10.13.128)/databasename", "username", "pass"
            smt = con.createStatement();

            if (con != null && !con.isClosed()) {
                System.out.println("Database Connected");
            } else {
                System.out.println("Not connected");
            }

            switch (ch) {
                case 1:
                    String st = "create table ";
                    Scanner sc = new Scanner(System.in);
                    System.out.println("Enter the name of the table: ");
                    String name = sc.nextLine();
                    System.out.println("Enter the attributes with the datatype: ");
                    String values = sc.nextLine();
                    st = st + name + "(" + values + ");";
                    System.out.println(st);
                    smt.executeUpdate(st);
                    System.out.println("Table is created!");
                    sc.close();
                    break;
                case 2:
                    String st1 = "insert into temp values( ";
                    Scanner sc2 = new Scanner(System.in);
                    System.out.println("Enter the values: ");
                    String val = sc2.nextLine();
                    st1 = st1 + val + ");";
                    System.out.println(st1);
                    smt.executeUpdate(st1);
                    System.out.println("Inserted data!");
                    sc2.close();
                    break;
                case 3:
                    String st2 = "update temp set name= ";
                    Scanner sc3 = new Scanner(System.in);
                    System.out.println("Enter the value to be updated: ");
                    int roll_no = sc3.nextInt();
                    sc3.nextLine(); // Consume the newline character
                    System.out.println("Enter new name: ");
                    String new_name = sc3.nextLine();
                    st2 = st2 + "'" + new_name + "' where rollno=" + roll_no + ";";
                    smt.executeUpdate(st2);
                    sc3.close();
                    break;
                case 4:
                    String st3 = "delete from temp where ";
                    Scanner sc4 = new Scanner(System.in);
                    System.out.println("Enter the constraints:");
                    String constraint = sc4.nextLine();
                    st3 = st3 + constraint;
                    smt.executeUpdate(st3);
                    sc4.close();
                    break;
                case 5:

                    Scanner sc5 = new Scanner(System.in);
                    System.out.println("Enter the name of the tableName: ");
                    String tableName = sc5.nextLine();
                    String selectQuery = "SELECT * FROM " + tableName;

                    try {
                        ResultSet resultSet = smt.executeQuery(selectQuery);
                        ResultSetMetaData rsmd = resultSet.getMetaData();
                        int columnCount = rsmd.getColumnCount();
                        for (int i = 1; i <= columnCount; i++) {
                            System.out.print(rsmd.getColumnName(i) + "\t");
                        }
                        System.out.println();

                        while (resultSet.next()) {
                            for (int i = 1; i <= columnCount; i++) {
                                System.out.print(resultSet.getString(i) + "\t");
                            }
                            System.out.println();
                        }

                        resultSet.close();
                    } catch (SQLException e) {
                        System.out.println(e);
                    }
                    break;

            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                if (smt != null) {
                    smt.close();
                }
                if (con != null) {
                    con.close();
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}