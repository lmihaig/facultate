public class Employee extends Person {
    private int registrationNumber;

    public Employee(String firstName, String lastName, int registrationNumber) {
        super(firstName, lastName);
        this.registrationNumber = registrationNumber;
    }

    public Employee(String firstName, String lastName) {
        super(firstName, lastName);
        this.setRegistrationNumber(0);
    }

    public int getRegistrationNumber() {
        return registrationNumber;
    }

    public void setRegistrationNumber(int registrationNumber) {
        this.registrationNumber = registrationNumber;
    }

    public void getTot() {
        this.getFullName();
        System.out.println(" " + this.getRegistrationNumber());
    }
}
