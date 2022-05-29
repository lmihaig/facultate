package com.company.read;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class WorkWithBufferedReader {

    public static void main(String[] args) {

        FileReader reader = null;
        BufferedReader buffer = null;
        String fileName = "Angajati.txt";

        // Try block to check exceptions
        try {

            // A Reader that reads creates an input
            // character stream
            // and reads characters from it
            reader = new FileReader(fileName);

            // Creating a BufferedReader object - default buffer size (8Kb)
            buffer = new BufferedReader(reader);

            // Custom input
            // A string to store the lines
            String line = "";

            // Stores the current time - when the reading operation started
            long initialTime = System.currentTimeMillis();
            while (true) {

                // Try block to check exceptions
                try {

                    // readLine() method of BufferedReader
                    // returns
                    //  a whole line at a time
                    line = buffer.readLine();
                }

                // Catch block to handle exceptions
                catch (IOException e) {

                    // Print the line where exception
                    // occurred
                    e.printStackTrace();
                }

                // When the read head reaches the "End Of
                // File" the readLine method returns null
                if (line == null)
                    break;

                // Prints the line
                System.out.println(line);
            }

            // Display the time taken to read the data
            System.out.println("\nTime taken : "
                    + (System.currentTimeMillis()
                    - initialTime) + " milliseconds");


        }

        // Catch block
        catch (FileNotFoundException e) {

            // print the exception only if
            // the file not found
            e.printStackTrace();
        }
        finally {
            // Try block to check exceptions
            try {

                // Close all the streams
                buffer.close();
                reader.close();
            }

            // Catching only exceptions those occurred
            // only during closing streams
            catch (IOException e) {

                // Prints the line number where exception
                // occurred
                e.printStackTrace();
            }
        }
    }
}
