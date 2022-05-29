package collections_exercise.collections.service;

import service_architecture.model.*;

import java.util.*;

public class WorkWithSet {
    /*
        Collections Framework
        Set<E>
            HashSet<E>
            LinkedHashSet<E>
            TreeSet<E>
     */
    public static void main(String[] args) {
        Set<String> cities = new HashSet<>();
        cities.add("Bucuresti");
        cities.add("Timisoara");
        cities.add("Brasov");
        cities.add("Bucuresti");
        cities.add("Cluj");

        cities.forEach(city -> System.out.println(city));

        Set<String> cities2 = new LinkedHashSet<>();
        cities2.add("Bucuresti");
        cities2.add("Timisoara");
        cities2.add("Brasov");
        cities2.add("Bucuresti");
        cities2.add("Cluj");

        System.out.println("Cities ordered by adding operation");
        cities2.forEach(city -> System.out.println(city));

        Set<String> cities3 = new TreeSet<>();
        cities3.add("Bucuresti");
        cities3.add("Timisoara");
        cities3.add("Brasov");
        cities3.add("Bucuresti");
        cities3.add("Cluj");

        System.out.println("Cities sorted by natural order");
        cities3.forEach(city -> System.out.println(city));

        Set<BankAccount> accounts = new TreeSet<>();
        accounts.add(new DebitBankAccount(
                new Client("name1", "address1", "email1"), 340, "12345", BankAccountStatus.OPEN,
                "1111222233334444", 1000));
        accounts.add(new SavingsBankAccount(
                new Client("name2", "address2", "email2"), 3800, "1111222233335555",
                BankAccountStatus.OPEN, 3));
        accounts.add(new SavingsBankAccount(
                new Client("name3", "address3", "email3"), 0, "1111777733335555", BankAccountStatus.CLOSED, 6));
        System.out.println("Accounts sorted by balance");
        accounts.forEach(account -> System.out.println(account));
    }
}
