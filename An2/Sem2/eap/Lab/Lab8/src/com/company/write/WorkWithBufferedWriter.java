package com.company.write;

import java.io.*;

public class WorkWithBufferedWriter {

    public static void main(String[] args) {
        //initializing FileWriter
        FileWriter myFile;
        try
        {
            myFile = new FileWriter("SomeText.txt");

            // Initialing BufferedWriter
            BufferedWriter textWriter = new BufferedWriter(myFile);
            System.out.println("Buffered Writer start writing :)");

            // Use of write() method to write the value in 'SomeText.txt' file
            // Write "Aprilie"
            textWriter.write("Aprilie");

            // Go to next line
            textWriter.newLine();

            // Write "2022"
            textWriter.write("2022");

            // Go to next line
            textWriter.newLine();

            // Write "Java class"
            textWriter.write("Operations in Java");

            // Closing BufferWriter to end operation
            textWriter.close();
            System.out.println("Written successfully");
        }
        catch (IOException except)
        {
            except.printStackTrace();
        }
    }
}
