package com.company;

import com.company.interfaces.Animal;
import com.company.interfaces.Innotator;
import com.company.interfaces.Zburator;

public class WorkWithInterfaces {
    public static void main(String[] args) {
        Animal a = new Animal();
        a.innoata();
        a.zboara();

        Innotator innotator = new Animal();
        innotator.innoata();

        Zburator zburator = new Animal();
        zburator.zboara();

        a.mananca();

    }
}
