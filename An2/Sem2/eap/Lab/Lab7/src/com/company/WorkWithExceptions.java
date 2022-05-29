package com.company;

public class WorkWithExceptions {
    public static void main(String[] args) {

        int a = 10 / 2;
        System.out.println(a);
        try {
            int b = 10 / 0;
            System.out.println(b);
        } catch (ArithmeticException e) {
            e.printStackTrace();
        } catch (RuntimeException e) {
            System.out.println("runtime");
        } finally {
            System.out.println("Test");
        }
        System.out.println("Test2");

    }
}
