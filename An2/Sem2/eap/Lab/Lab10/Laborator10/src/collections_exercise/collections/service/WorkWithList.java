package collections_exercise.collections.service;

import service_architecture.model.*;

import java.util.*;

public class WorkWithList {
    /*
        Collections Framework
        List<E>
     */
    public static void main(String[] args) {
        List<BankAccount> accounts = new ArrayList<>();
        accounts.add(new DebitBankAccount(
                new Client("name1", "address1", "email1"), 300,
                "1111222233334444", BankAccountStatus.OPEN, "34567654", 1000));
        accounts.add(new SavingsBankAccount(
                new Client("name2", "address2", "email2"), 300, "1111222233335555",
                BankAccountStatus.SUSPENDED, 3));
        accounts.add(new SavingsBankAccount(
                new Client("name3", "address3", "email3"), 200,"1111777733335555",
                BankAccountStatus.OPEN, 12));

//        System.out.println(accounts.get(1));

        for(BankAccount account : accounts) {
            System.out.println(account);
        }

        accounts.remove(0);
        accounts.clear();

        List<BankAccount> newAccounts = new ArrayList<>();
        newAccounts.add(new DebitBankAccount(
                new Client("name1", "address1", "email1"), 250, "159874", BankAccountStatus.OPEN,
                "1111888833334444", 10000));
        newAccounts.add(new DebitBankAccount(
                new Client("name2", "address2", "email2"), 2400, "1000236", BankAccountStatus.OPEN,
                "1111888833334444", 10000));
        accounts.addAll(newAccounts);

        System.out.println("Accounts with the new accounts:");
        accounts.forEach(account -> System.out.println(account));

        List<Integer> numbers = new ArrayList<>();
        numbers.add(1);
        numbers.add(Integer.valueOf("2"));

        Collections.sort(accounts);
        System.out.println("Accounts sorted by balance:");
        accounts.forEach(account -> System.out.println(account));
    }
}
