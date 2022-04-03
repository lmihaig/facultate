
import util.*;

public class App {

    public static void main(String[] args) {
        Person p1 = new Person();
        Person p2 = new Person("Ionut", "Testescu");
        System.out.println(p1.getFirstName() + " " + p1.getLastName());
        p2.getFullName();
        p1.getFullName(1);

        Employee e1 = new Employee("Treispezescu", "Adiwao241p[q=^");
        Employee e2 = new Employee("Popescu", "Ionescu");
        System.out.println(e2.getRegistrationNumber());
        e1.getFullName();

        // Registration r1 = new Registration();
        // Registration r2 = new Registration();
        // RegNumberGeneratorSingleton r3 = new RegNumberGeneratorSingleton(); // nu
        // mere

        Employee e3 = new Employee("Dudescu", "Viezure", RegNumberGeneratorSingleton.getInstance().getNewCode());
        Employee e4 = new Employee("Dudescu", "Ionut", RegNumberGeneratorSingleton.getInstance().getNewCode());

        e3.getTot();
        e4.getTot();
    }
}
