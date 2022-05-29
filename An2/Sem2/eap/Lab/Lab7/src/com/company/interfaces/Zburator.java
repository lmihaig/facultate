package com.company.interfaces;

public interface Zburator {

    void zboara();

    default void mananca() {
        System.out.println("Zburatorul mananca");
    }
}
