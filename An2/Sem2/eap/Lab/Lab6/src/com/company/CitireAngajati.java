package com.company;

import com.company.domain.Employee;
import com.company.domain.Person;
import com.company.util.RegNumberGeneratorSingleton;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class CitireAngajati {
    public static void main(String[] args) throws FileNotFoundException {

        Scanner in = new Scanner(new File("Angajati_cu_dubluri.txt"));
        int n = in.nextInt();
        in.nextLine();
        Employee[] employees = new Employee[n];

        String line;
        for (int i = 0; i < n; i++) {
            line = in.nextLine();
            String[] aux = line.split("\\s+");
            employees[i] = new Employee(aux[0], aux[1]);
        }

        /**
         * Se afiseaza tabloul de angajati folosind clasa utilitara Arrays.
         * Conform implementarii metodei Arrays.toString(Object[] a),
         * se apeleaza metoda toString a clasei Employee
         * Metoda toString a clasei Employee este mostenita din clasa Object
         * dar a fost suprascrisa pentru a afisa proprietatile care au sens pentru
         * utilizator.
         */
        System.out.println(
                "\nSTART ************ Afisare angajati identificati in fisierul Angajati_cu_dubluri.txt *********");
        System.out.println(Arrays.toString(employees));
        System.out.println(
                "\nEND ******************************************************************************************");

        // Cum testam egalitatea dintre doua persoane?
        Person p1 = new Person("Mara", "Popescu");
        Person p2 = new Person("Mara", "Popescu");

        /**
         * In Java testarea egalitatii dintre doua obiecte se poate face
         * prin compararea referintelor sau prin utilizarea metodei equals.
         * Compararea referintelor nu tine cont de valoarea obiectului,
         * astfel, pentru o comparatie bazata pe valori din interiorul obiectului,
         * este necesara utilizarea metodei equals.
         * Metoda equals poate fi suprascrisa in functie de necesitatile programului.
         */
        System.out.println("\nAvem egalitate intre p1 si p2? " + (p1 == p2));
        System.out.println("\nAvem egalitate intre p1 si p2? " + (p1.equals(p2)));

        // TODO: Rescrieti metoda equals a clasei Person astfel incat 'p1.equals(p2)' sa
        // returneze 'true'
        // done

        // TODO: Adaugare angajati unici in tabloul de angajati (dupa firstName si
        // lastName)
        /**
         * Guidelines:
         * - se reinitializea obiectul de tip Scanner (in)
         * - se mapeaza liniile din fisierul .txt la obiecte de tip Person
         * (pentru a nu irosi numere de inregistrare si a ne folosi de metoda equals)
         * - persoanele identificate in fisier se stocheaza intr-o colectie cu
         * dimensiune variabila
         * (putem initializa un tablou - e.g. Person[] caruia sa nu ii cunoastem
         * dimensiunea exacta?)
         * - pentru fiecare persoana unica identificata in fisier se genereaza un
         * angajat intr-o noua structura de date
         */
        // TODO
        in = new Scanner(new File("Angajati_cu_dubluri.txt"));
        n = in.nextInt();
        in.nextLine();
        ArrayList<Person> uniquePerson = new ArrayList<Person>();

        boolean exists;
        for (int i = 0; i < n; i++) {
            exists = false;
            line = in.nextLine();
            String[] aux = line.split("\\s+");
            Person newPerson = new Person(aux[0], aux[1]);
            for (Person p : uniquePerson) {
                if (p.equals(newPerson))
                    exists = true;
            }
            if (!exists)
                uniquePerson.add(newPerson);
        }

        System.out.println(Arrays.toString(uniquePerson.toArray()));
        Employee[] emparray = new Employee[uniquePerson.size()];
        int i = 0;
        for (Person p : uniquePerson) {
            Employee newEmployee = new Employee(p.getFirstName(), p.getLastName());
            emparray[i] = newEmployee;
            i++;
        }
        System.out.println(Arrays.toString(emparray));
    }
}
