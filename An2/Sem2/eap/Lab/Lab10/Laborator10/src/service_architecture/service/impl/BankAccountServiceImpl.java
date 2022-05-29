package service_architecture.service.impl;

import service_architecture.model.*;
import service_architecture.service.BankAccountService;
import service_architecture.service.ClientService;

import java.util.*;

import static service_architecture.model.BankAccountStatus.*;

public class BankAccountServiceImpl implements BankAccountService {
    private static final Random RANDOM = new Random();
    private ClientService clientService;

    public BankAccountServiceImpl(ClientService clientService) {
        this.clientService = clientService;
    }

    @Override
    public List<BankAccount> getBankAccounts() {
        List<Client> clients = clientService.getClients();
        return List.of(
                new DebitBankAccount(clients.get(0), 7000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, String.valueOf(RANDOM.nextInt(16)), 1000),
                new DebitBankAccount(clients.get(1), 5400, String.valueOf(RANDOM.nextInt(10)),
                        BankAccountStatus.CLOSED, String.valueOf(RANDOM.nextInt(16)), 0),
                new DebitBankAccount(clients.get(2), 600, String.valueOf(RANDOM.nextInt(10)),
                        BankAccountStatus.CLOSED, String.valueOf(RANDOM.nextInt(16)), 2000),
                new DebitBankAccount(clients.get(3), 9300, String.valueOf(RANDOM.nextInt(10)),
                        BankAccountStatus.SUSPENDED, String.valueOf(RANDOM.nextInt(16)), 10000),
                new DebitBankAccount(clients.get(4), 400, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, String.valueOf(RANDOM.nextInt(16)), 1000),
                new DebitBankAccount(clients.get(5), 37000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, String.valueOf(RANDOM.nextInt(16)), 1000),
                new SavingsBankAccount(clients.get(6), 55000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, 3),
                new SavingsBankAccount(clients.get(7), 30000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, 6),
                new SavingsBankAccount(clients.get(2), 12000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, 3),
                new SavingsBankAccount(clients.get(5), 486000, String.valueOf(RANDOM.nextInt(10)),
                        CLOSED, 9),
                new SavingsBankAccount(clients.get(7), 78000, String.valueOf(RANDOM.nextInt(10)),
                        SUSPENDED, 3),
                new SavingsBankAccount(clients.get(7), 4000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN, 6),
                new SavingsBankAccount(clients.get(1), 9000, String.valueOf(RANDOM.nextInt(10)),
                        OPEN,3)
        );
    }

    @Override
    public long getNumberOfBankAccountsForEmail(List<BankAccount> bankAccounts, String clientEmail) {
        return bankAccounts.stream()
                .filter(bankAccount -> bankAccount.getClient() != null &&
                                bankAccount.getClient().getEmail() != null &&
                        bankAccount.getClient().getEmail().equals(clientEmail))
                .count();
    }

    @Override
    public void printUniqueClientDetails(List<BankAccount> bankAccounts) {
        bankAccounts.stream()
                .map(BankAccount::getClient)
                .distinct()
                .forEach(client -> System.out.println(client.getName() + " / " +
                        client.getEmail()));
    }

    @Override
    public void printSavingsBankAccountsByBalance(List<BankAccount> bankAccounts) {
        bankAccounts.stream()
                .filter(bankAccount -> bankAccount instanceof SavingsBankAccount)
                .sorted(Comparator.reverseOrder())
                .forEach(System.out::println); //method reference
    }
}
