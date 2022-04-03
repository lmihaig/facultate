package com.company.immutability;

/**
 * O clasa este imutabila daca o instanta clasei respective nu mai poate fi
 * modificata dupa ce a fost creata.
 * Clase imutabile din JDK: String, Integer, Float etc.
 *
 * TODO Modificati clasa ImmutablePerson astfel incat instantele acesteia sa fie
 * imutabile.
 * Guidelines:
 * - adaugati modificatorul de acces final la nivelul clasei
 * - proprietatile sa fie private si final (optional)
 * - proprietatile sa nu poata fi modificate prin setters
 * - metodele de tip getter sa returneze copii (clone) ale proprietatilor
 * - constructorul creaza clone ale obiectelor primite ca parametri
 * (astfel incat valorile proprietatilor sa nu poata fi modificate prin alte
 * referinte)
 */
public class ImmutablePerson {

    public String firstName;
    public String lastName;
    public Country country;

    public ImmutablePerson() {
    }

    public ImmutablePerson(String firstName, String lastName, Country country) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.country = country;
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

    public Country getCountry() {
        return country;
    }

    public void setCountry(Country country) {
        this.country = country;
    }
}
