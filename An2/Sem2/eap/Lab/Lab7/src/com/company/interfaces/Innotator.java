package com.company.interfaces;

public interface Innotator {

    void innoata();

    default void mananca() {
        System.out.println("Innotatorul mananca");
    }
}
