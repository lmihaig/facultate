package main.config;

import java.sql.*;

public class DatabaseConnection {
    private static Connection connection;

    private DatabaseConnection () {

    }

    public static Connection getInstance() throws SQLException {

        if(connection == null) {
            String url = "jdbc:mysql://localhost:3306/pao_lab_11";
            String username = "root";
            String password = "pao11";
            connection = DriverManager.getConnection(url, username, password);
        }
        return connection;
    }
}
