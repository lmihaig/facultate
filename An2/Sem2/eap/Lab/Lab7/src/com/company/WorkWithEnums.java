package com.company;

import com.company.enums.CountryEnum;
import com.company.enums.Continent;
import com.company.interfaces.Animal;

public class WorkWithEnums {
    public static void main(String[] args) {
        // TODO adaugati o proprietate cu numele 'provenienta' de tipul ContryEnum in
        // clasa Animal
        // setati proprietatea prin constructor si definiti o metoda de tip getter
        // pentru aceasta
        // afisati codul telefonic al tarii de provenienta pentru obiectul de tip Animal
        // creat

        Animal pinguin = new Animal(CountryEnum.ROMANIA);
        System.out.println(pinguin.getProvenienta().getCode());

        System.out.println(java.util.Arrays.asList(Continent.values()));

    }
}
