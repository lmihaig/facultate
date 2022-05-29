package main;

import main.model.*;
import main.service.*;

import java.util.*;

public class Application {
    public static void main(String[] args) {
        BankAccountService bankAccountService = new BankAccountService();

        Scanner scanner = new Scanner(System.in);

        while(true) {
            System.out.println("Please type one of the following commands: create, get, get total amount, exit");
            String line = scanner.nextLine();
            switch(line) {
                case "create" : {
                    addBankAccount(bankAccountService, scanner);
                    break;
                }
                case "get" : {
                    Optional<BankAccount> bankAccount =
                            bankAccountService.getBankAccountById(Long.valueOf(scanner.nextLine()));
                    if(bankAccount.isPresent()) {
                        System.out.println(bankAccount.get());
                    }
                    break;
                }
                case "get total amount" : {
                    System.out.println("Please specify the bank account type: ");
                    System.out.println(bankAccountService.getTotalAmountByType(BankAccountType.valueOf(scanner.nextLine())));
                    break;
                }
                case "exit" : {
                    System.out.println("Bye...");
                    System.exit(0);
                }
                default : System.out.println("This command doesn't exist.");
            }
        }
    }

    private static void addBankAccount(BankAccountService bankAccountService, Scanner scanner) {

        System.out.println("Please specify the bank account details: accountNumber/balance/type/cardNumber");
        try {
            BankAccount bankAccount = bankAccountService.build(scanner.nextLine());
            bankAccountService.addBankAccount(bankAccount);
        } catch (NumberFormatException e) {
            System.out.println("Invalid inputs for bank account creation. The bank account was not saved in the db.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Not enough inputs for bank account creation. The bank account was not saved in the db.");
        }
    }
}
