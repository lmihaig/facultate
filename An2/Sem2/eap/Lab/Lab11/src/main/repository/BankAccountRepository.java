package main.repository;

import main.config.*;
import main.model.*;

import java.sql.*;
import java.util.*;

public class BankAccountRepository {
    /*
    *   Statement
    *   PreparedStatement
    *   CallableStatement
    *
    * */

    public void addBankAccount(BankAccount bankAccount) {
        String sql = "insert into bankaccounts values (null, ?, ?, ?, ?) ";
        try (PreparedStatement statement = DatabaseConnection.getInstance().prepareStatement(sql)) {//try with resources
          statement.setString(1, bankAccount.getAccountNumber());
          statement.setDouble(2, bankAccount.getBalance());
          statement.setString(3, bankAccount.getType().toString());
          statement.setString(4, bankAccount.getCardNumber());
          statement.executeUpdate();
        } catch(SQLException e) {
            e.printStackTrace();
        }
    }

    public Optional<BankAccount> getBankAccountById(long id) {
        String sql = "select * from bankaccounts ba where ba.id = ?";
        try(PreparedStatement statement = DatabaseConnection.getInstance().prepareStatement(sql)) {
            statement.setLong(1, id);
            ResultSet result = statement.executeQuery();
            while(result.next()) {
                //i have at least one record in the result set
                long bankAccountId = result.getLong(1);
                String accountNumber = result.getString("accountNumber");
                double balance = result.getDouble("balance");
                BankAccountType type = BankAccountType.valueOf(result.getString("type"));
                String cardNumber = result.getString("cardNumber");
                return Optional.of(new BankAccount(bankAccountId, accountNumber, balance, type, cardNumber));
            }
        } catch(SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public double getTotalAmountByType(BankAccountType type) {
        double result = 0;

        String sql = "{? = call total_amount_per_type(?)}";

        try (CallableStatement stmt = DatabaseConnection.getInstance().prepareCall(sql)) {
            stmt.registerOutParameter(1, Types.DOUBLE);
            stmt.setString(2, type.toString());
            stmt.execute();
            result = stmt.getDouble(1);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;
    }
}
