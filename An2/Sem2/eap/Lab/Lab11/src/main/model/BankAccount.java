package main.model;

public class BankAccount {
    private long id;
    private String accountNumber;
    private double balance;
    private BankAccountType type;
    private String cardNumber;

    public BankAccount() {
    }

    public BankAccount(String accountNumber, double balance, BankAccountType type, String cardNumber) {
        this.accountNumber = accountNumber;
        this.balance = balance;
        this.type = type;
        this.cardNumber = cardNumber;
    }

    public BankAccount(long id, String accountNumber, double balance, BankAccountType type, String cardNumber) {
        this.id = id;
        this.accountNumber = accountNumber;
        this.balance = balance;
        this.type = type;
        this.cardNumber = cardNumber;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getAccountNumber() {
        return accountNumber;
    }

    public void setAccountNumber(String accountNumber) {
        this.accountNumber = accountNumber;
    }

    public double getBalance() {
        return balance;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }

    public BankAccountType getType() {
        return type;
    }

    public void setType(BankAccountType type) {
        this.type = type;
    }

    public String getCardNumber() {
        return cardNumber;
    }

    public void setCardNumber(String cardNumber) {
        this.cardNumber = cardNumber;
    }

    @Override
    public String toString() {
        return  id +
                ", " + accountNumber +
                ", " + balance +
                ", " + type +
                ", " + cardNumber;
    }
}
