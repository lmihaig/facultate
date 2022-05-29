package service_architecture.main;

import service_architecture.model.*;
import service_architecture.service.*;
import service_architecture.service.impl.BankAccountServiceImpl;

import java.util.*;

public class Main {
    public static void main(String[] args) {

        BankAccountService bankAccountService = new BankAccountServiceImpl(ClientService.getInstance());
        List<BankAccount> bankAccounts = bankAccountService.getBankAccounts();

        System.out.println("Number of bank accounts for test@gmail.com: " +
                bankAccountService.getNumberOfBankAccountsForEmail(bankAccounts, "test@gmail.com"));

        bankAccountService.printUniqueClientDetails(bankAccounts);

        bankAccountService.printSavingsBankAccountsByBalance(bankAccounts);

        /**
         * TODO Implement a new Service named BCRBankAccountServiceImpl that implements BankAccountService
         * The new servicearchitecture.service provides a list of BCR clients by reading clienti-bcr.txt file that has tab-delimited data
         * First line of the header contains the name of the columns
         * Call the methods of the BCR servicearchitecture.service - printUniqueClientDetails, printSavingsBankAccountsByBalance
         * using the client details read from txt
         */

    }


}
