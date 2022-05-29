package com.company.immutability;

public class Country {
    private String name;
    private String phoneCode;

    public Country(String name, String phoneCode) {
        this.name = name;
        this.phoneCode = phoneCode;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhoneCode() {
        return phoneCode;
    }

    public void setPhoneCode(String phoneCode) {
        this.phoneCode = phoneCode;
    }

    @Override
    public String toString() {
        return "Country{" +
                "name='" + name + '\'' +
                ", phoneCode='" + phoneCode + '\'' +
                '}';
    }
}
