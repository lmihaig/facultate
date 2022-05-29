package com.company.read;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class WorkWithFileReader {

    public static void main(String[] args) {

        FileReader reader = null;
        String fileName = "Angajati.txt";

        // Try-catch-finally block to check if an exception occurs when creating the reader
        try {

            // Creating a FileReader to read data from a file on the disk
            reader = new FileReader(fileName);

            char ch;

            // An integer to store the integer returned by FileReader#read() method
            int i = -1;

            // Stores the current time - when the reading operation started
            long initialTime = System.currentTimeMillis();

            while (true) {
                try {
                    // The read() method of FileReader
                    // reads one character at a time
                    // and returns it as an integer
                    i = reader.read();
                } catch (IOException e) {
                    e.printStackTrace();
                }

                // When the "End Of File" is reached
                // the read() method returns -1
                if (i == -1)
                    break;

                ch = (char) i;
                System.out.print(ch);
            }

            // Print the duration of the reading operation
            System.out.println("\nTime taken : "
                    + (System.currentTimeMillis()
                    - initialTime) + " milliseconds");


        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}