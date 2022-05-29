package service_architecture.model;

public enum BankAccountStatus {
    OPEN("bank account is open"),
    CLOSED("bank account is closed, cannot be reopend"),
    SUSPENDED("bank account suspended, can be reopened");

    private String description;

    private BankAccountStatus(String description) {
        this.description = description;
    }

    public String getDescription() {
        return description;
    }
}
