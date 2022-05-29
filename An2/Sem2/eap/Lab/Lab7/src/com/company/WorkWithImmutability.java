package com.company;

import com.company.immutability.Country;
import com.company.immutability.ImmutableEmployee;
import com.company.immutability.ImmutablePerson;

public class WorkWithImmutability {

    public static void main(String[] args) {
        /**
         * Extinderea clasei ImmutablePerson
         */
        ImmutableEmployee e = new ImmutableEmployee();
        System.out.println("Immutable employee: " + e);

        /**
         * Criteriu imutabilitate 1
         * Pentru ca o clasa sa fie imutabila aceasta nu trebuie sa poata fi extinsa.
         *
         * TODO Adaugati modificatorul de acces final la nivelul clasei ImmutablePerson
         */

        // Creare persoana
        Country ro = new Country("Romania", "+40");
        ImmutablePerson p1 = new ImmutablePerson("Ana", "Popa", ro);
        System.out.println("Detalii persoana: " + p1);

        /**
         * Modificarea proprietatii firstName prin atribuire directa
         */
        // p1.firstName = "Ana-Maria";
        System.out.println("Persoana cu firstName modificat: " + p1);

        /**
         * Criteriu imutabilitate 2
         * Pentru ca un obiect sa fie imutabil,
         * proprietatile acestuia trebuie sa fie declarate private si final (optional)
         *
         * TODO Modificati clasa ImmutablePerson.java astfel incat sa corespunda acestui
         * criteriu.
         */

        /**
         * Modificarea proprietatii firstName prin metoda de tip setter
         */
        // p1.setFirstName("Ionela");
        System.out.println("Persoana cu firstName modificat: " + p1);

        /**
         * Criteriu imutabilitate 3
         * Pentru ca un obiect sa fie imutabil,
         * proprietatile nu trebuie sa poata fi modificate prin metode de tip setter
         *
         * TODO Modificati clasa ImmutablePerson.java astfel incat sa corespunda acestui
         * criteriu.
         */

        /**
         * Modificarea proprietatii country prin schimbarea proprietatilor obiectului
         * referentiat.
         */
        Country originalCountry = p1.getCountry();
        System.out.println("Tara persoanei la instantierea obiectului: " + p1.getCountry());
        System.out.println("Detalii persoana inainte de schimbarea tarii: " + p1);

        originalCountry.setName("Italia");
        originalCountry.setPhoneCode("+39");
        System.out.println("Tara persoanei dupa schimbarea proprietatii prin alterarea obiectului referentiat: "
                + p1.getCountry());
        System.out.println("Detalii persoana dupa schimbarea tarii: " + p1);

        /**
         * Criteriu imutabilitate 4
         * Metodele de tip getter sa returneze copii (clone) ale proprietatilor
         *
         * TODO Modificati clasa ImmutablePerson.java astfel incat sa corespunda acestui
         * criteriu.
         * Starea obiectului Country ce apartine obiectului ImmutablePerson
         * sa nu poata fi modificata dupa instantierea clasei ImuutablePerson
         */

        Country newCountry = new Country("Grecia", "+30");
        ImmutablePerson p2 = new ImmutablePerson("Mihnea", "Ionescu", newCountry);
        System.out.println("Detalii p2 dupa initializare: " + p2);

        // Modificare obiect de tip Country folosit la initializarea obiectului p2
        newCountry.setName("Bulgaria");
        newCountry.setPhoneCode("+359");

        System.out.println("Detalii p2 dupa modificarea obiectului newCountry: " + p2);

        /**
         * Criteriu imutabilitate 5
         * Constructorul creaza clone ale obiectelor primite ca parametri
         * (astfel incat valorile proprietatilor sa nu poata fi modificate prin alte
         * referinte)
         *
         * TODO Modificati clasa ImmutablePerson.java astfel incat sa corespunda acestui
         * criteriu.
         */

    }
}
