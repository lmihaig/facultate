package com.company.domain;

import java.util.Objects;

public class Person {

    private String firstName = "Ion";
    private String lastName = "Popescu";

    public Person() {
    }

    public String getFullName() {
        return this.firstName + " " + this.lastName;
    }

    public Person(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    // Code generated using Intellij IDEA
    /**
     * According to equals - hashCode contract, these methods should be overridden
     * together
     * and the implementation of both methods should include the same properties
     * (e.g. firstName and lastName).
     */
    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || (getClass() != o.getClass()))
            return false;
        Person person = (Person) o;
        return firstName.equals(person.firstName) && lastName.equals(person.lastName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstName, lastName);
    }
}
