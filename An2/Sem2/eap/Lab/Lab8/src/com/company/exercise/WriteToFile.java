package com.company.exercise;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.company.domain.Employee;
import com.company.domain.Person;

public class WriteToFile {
    public static void main(String[] args) {
        /**
         * Construiti fisierul AngajatiUnici.txt
         * care contine toti angajatii din fisierul Angajati.txt,
         * dupa ce s-au eliminat duplicatele
         */

        // Citire fisier Angajati.txt utilizand clasa BufferedReader
        // INSERT CODE BELOW
        FileReader reader = null;
        BufferedReader buffer = null;
        String fileName = "Angajati.txt";
        FileWriter myFile;

        try {

            reader = new FileReader(fileName);

            buffer = new BufferedReader(reader);

            myFile = new FileWriter("AngajatiUnici.txt");
            BufferedWriter textWriter = new BufferedWriter(myFile);
            String line = "";
            boolean foundDuplicate;
            List<Person> uniquePersons = new ArrayList<>();

            while (true) {
                try {
                    line = buffer.readLine();
                    if (line != null) {
                        String[] aux = line.split("\\s+");
                        Person auxPerson = new Person(aux[0], aux[1]);
                        foundDuplicate = false;
                        for (Person p : uniquePersons) {
                            if (auxPerson.equals(p)) {
                                foundDuplicate = true;
                                break;
                            }
                        }
                        if (!foundDuplicate) {
                            uniquePersons.add(new Person(aux[0], aux[1]));
                        }
                    }
                } catch (IOException e) {

                    e.printStackTrace();
                }

                if (line == null)
                    break;

            }
            // Pentru fiecare linie citita din fisier se va crea un obiect Person
            // daca nu este identificata ca fiind dublura
            // INSERT CODE BELOW
            List<Employee> uniqueEmployees = new ArrayList<>();
            for (Person uniquePerson : uniquePersons) {
                uniqueEmployees.add(new Employee(uniquePerson.getFirstName(), uniquePerson.getLastName()));
            }
            // Scriere fisier AngajatiUnici.txt utilizand clasa BufferedWriter
            // INSERT CODE BELOW
            for (Employee e : uniqueEmployees) {
                textWriter.write(e.getRegistrationNumber().toString());
                textWriter.write(" ");
                textWriter.write(e.getFullName());
                textWriter.newLine();

            }

            textWriter.close();
            System.out.println("Written successfully");
        }
        // Catch block
        catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {

            e.printStackTrace();
        } finally {
            try {

                buffer.close();
                reader.close();
            }

            catch (IOException e) {

                e.printStackTrace();
            }
        }

    }
}
