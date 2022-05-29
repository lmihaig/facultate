package com.company.interfaces;

import com.company.enums.CountryEnum;

public class Animal implements Innotator, Zburator {
    private CountryEnum provenienta;

    public Animal() {
    }

    public Animal(CountryEnum provenienta) {
        this.provenienta = provenienta;
    }

    public CountryEnum getProvenienta() {
        return provenienta;
    }

    @Override
    public void innoata() {
        System.out.println("Innoata");
    }

    @Override
    public void zboara() {
        System.out.println("Zboara");
    }

    @Override
    public void mananca() {
        Zburator.super.mananca();
    }

    
}
