
public class Person {

    private String firstName;
    private String lastName;

    public Person() {

        this.firstName = "Testescu";
        this.lastName = "Ion";
    }

    public Person(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public void setFirstName(String firstname) {
        this.firstName = firstname;

    }

    public void setLastName(String lastname) {
        this.lastName = lastname;

    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void getFullName() {
        System.out.println(this.firstName + " " + this.lastName);
    }

    public void getFullName(int order) {
        if (order == 1)
            System.out.println(this.lastName + " " + this.firstName);
        else
            System.out.println(this.firstName + " " + this.lastName);

    }
}
