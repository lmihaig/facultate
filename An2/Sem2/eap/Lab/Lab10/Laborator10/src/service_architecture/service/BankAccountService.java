package service_architecture.service;

import service_architecture.model.BankAccount;

import java.util.List;

public interface BankAccountService {
    /**
     * Get a list of all BankAccounts
     * @return list of BankAccounts
     */
    List<BankAccount> getBankAccounts();

    /**
     *
     * @param bankAccounts
     * @param clientEmail
     * @return
     */
    long getNumberOfBankAccountsForEmail(List<BankAccount> bankAccounts, String clientEmail);

    /**
     *
     * @param bankAccounts
     */
    void printUniqueClientDetails(List<BankAccount> bankAccounts);

    /**
     *
     * @param bankAccounts
     */
    void printSavingsBankAccountsByBalance(List<BankAccount> bankAccounts);
}
