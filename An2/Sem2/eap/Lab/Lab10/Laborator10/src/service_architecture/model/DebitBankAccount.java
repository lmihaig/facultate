package service_architecture.model;

public class DebitBankAccount extends BankAccount {
    private String cardNumber;
    private double withdrawalLimit;

    public DebitBankAccount(Client client, double balance, String accountNumber,
                            BankAccountStatus status, String cardNumber, double withdrawalLimit) {
        super(client, balance, accountNumber, status);
        this.cardNumber = cardNumber;
        this.withdrawalLimit = withdrawalLimit;
    }

    public String getCardNumber() {
        return cardNumber;
    }

    public void setCardNumber(String cardNumber) {
        this.cardNumber = cardNumber;
    }

    public double getWithdrawalLimit() {
        return withdrawalLimit;
    }

    public void setWithdrawalLimit(double withdrawalLimit) {
        this.withdrawalLimit = withdrawalLimit;
    }

    @Override
    public String toString() {
        return super.toString() + " / " + this.cardNumber + " / " + withdrawalLimit;
    }
}
