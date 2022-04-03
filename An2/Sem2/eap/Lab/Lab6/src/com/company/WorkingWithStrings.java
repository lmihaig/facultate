package com.company;

public class WorkingWithStrings {
    public static void main(String[] args) {
        // String vs StringBuilder vs StringBuffer

        /**
         * Creating Strings without using the 'new' keyword.
         * This way the objects are added to the StringPool.
         * The StringPool is storing only one copy of each literal String in the pool.
         */
        String s1 = "Hello";
        String s2 = "Hello";
        System.out.println("Is s1 referencing the same object as s2? " + (s1 == s2));

        /**
         * Creating Strings using the 'new' keyword.
         * This way the objects are added to the HEAP.
         */
        String s3 = new String("Hello");
        System.out.println("Is s1 referencing the same object s3? " + (s1 == s3));

        System.out.println("Is the value referenced by s1 " +
                "the same with the one referenced by s3? " + s1.equals(s3));

        /**
         * Strings can be manually added to the String pool by using the .intern()
         * method.
         * intern() method returns a new String, it does not modify the original String
         * Before Java 7, String pool was stored in PermGen then it was moved to Heap
         */
        String s4 = s3.intern();
        System.out.println("Are s4 and s3 referencing the same object? " + (s3 == s4));
        System.out.println("Are s4 and s2 referencing the same object? " + (s2 == s4));

        /**
         * Strings are immutable. Once the value of a String object was created, it
         * cannot be changed.
         * Thus, the instruction below adds new String objects to the StringPool
         */
        s1 = s1 + " World";
        System.out.println(s1);
        System.out.println(s2);
        System.out.println("Is s1 STILL referencing the same object as s2? " + (s1 == s2));

        /**
         * In oredr to execute many operations on String objects,
         * we can use classes that are built to execute these operations optimal.
         * These classes are StringBuilder and StringBuffer. Both have same methods,
         * but while StringBuilder is faster, StringBuffer is thread-safe.
         */

        /**
         * StringBuilder
         * This class can manipulate String objects faster than StringBuffer but it is
         * not thread-safe.
         */
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("ana").append("are").append("mere").reverse();
        System.out.println("StringBuilder - getting reversed value: " + stringBuilder);

        /**
         * StringBuffer
         * /* This class manipulates Strings slower than StringBuilder class,
         * but it is thread-safe (can be used by multiple threads at the same time).
         * All methods of StringBuffer are synchronized and only one thread can execute
         * a method at a time.
         */
        StringBuffer stringBuffer = new StringBuffer();
        stringBuffer.append("ana").append("are").append("mere").reverse();
        System.out.println("StringBuffer - getting reversed value: " + stringBuffer);

    }
}
