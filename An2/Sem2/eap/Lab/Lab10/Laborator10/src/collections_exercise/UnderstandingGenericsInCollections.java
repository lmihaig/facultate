package collections_exercise;

import java.util.ArrayList;
import java.util.List;

public class UnderstandingGenericsInCollections {
    public static void main(String[] args)  {
        /**
         * create collection of type List without specifying the type of the elements using generics
         * this allows Objects with different type to be added to the same Collection
         */
        List aList = new ArrayList();
        aList.add(3);
        aList.add(new String("someString"));
        aList.add(Boolean.TRUE);

        //this list can only be iterated with an Object => for (Object o : aList)
        // as Object is the common parent class of all elements in the collection
        for (Object o : aList) {
            System.out.print(o);
            System.out.print(" of type " + o.getClass() + "\n");
        }

        /**
         *  create collection of type List specifying the type of the elements using generics
         *  this allows Objects with same type to be added to the same Collection
         */

        List<Integer> integers = new ArrayList<>();
        integers.add(1);
        integers.add(4);
        integers.add(6);
        integers.add(100);
        integers.add(12);
        integers.add(9);

        //this list can be iterated with an Integer as we know the type of each object => for (Integer i : integers)
        //the methods of class type specified through generics can be directly accessed
        for (Integer i : integers) {
            System.out.println(i);
        }


    }
}
