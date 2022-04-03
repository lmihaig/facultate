package com.company.domain;

import com.company.util.RegNumberGeneratorSingleton;

public class Employee extends Person {

    private Integer registrationNumber;

    public Employee() {
    }

    public Employee(String firstName, String lastName) {
        super(firstName, lastName);
        this.registrationNumber = RegNumberGeneratorSingleton.getInstance().getNewCode();
    }

    public Integer getRegistrationNumber() {
        return registrationNumber;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "registrationNumber=" + registrationNumber +
                ", firstName='" + this.getFirstName() + '\'' +
                ", lastName='" + this.getLastName() + '\'' +
                "}\n";
    }
}
