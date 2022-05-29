package com.company.exercise;


import com.company.domain.Employee;
import com.company.domain.Person;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class SelectUniqueEmployeesUsingScanner {
    public static void main(String[] args) throws FileNotFoundException {

        //Reading first line in the file using Scanner class
        Scanner in = new Scanner(new File("Angajati_cu_dubluri.txt"));

        //The first line in the file holds the number of lines to be read
        int n = in.nextInt();
        in.nextLine();

        //Initialize a list of Persons
        // where a new Person will be added if it doesn't already exists in the list
        List<Person> uniquePersons = new ArrayList<>();

        //Algorithm that identifies if the line currently read
        //describes a new Person or a Person that was previously read from the file
        boolean foundDuplicate;
        String line;
        for(int i = 0; i < n; i++)
        {
            line = in.nextLine();
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

        //After all lines were read, each Person in the list translates to a new Employee
        List<Employee> uniqueEmployees = new ArrayList<>();
        for (Person uniquePerson : uniquePersons) {
            uniqueEmployees.add(new Employee(uniquePerson.getFirstName(), uniquePerson.getLastName()));
        }

        //Printing the list of unique employees
        System.out.println("\nSTART ************ Afisare angajati UNICI identificati in fisierul Angajati_cu_dubluri.txt *********");
        System.out.println(Arrays.toString(uniqueEmployees.toArray()));
        System.out.println("\nEND ************************************************************************************************");
    }
}
