package collections_exercise.collections.service;

import java.util.*;

public class WorkWithMap {
    /*
        Collection Framework

        Map<K, V>
            HashMap<K, V>
            LinkedHashMap<K, V>
            TreeMap<K, V>
     */
    public static void main(String[] args) {
        Map<String, Integer> cities = new HashMap<>();
        cities.put("Bucuresti", 2000000);
        cities.put("Timisoara", 700000);
        cities.put("Cluj", 1500000);
        cities.put("Bucuresti", 2100000);
        cities.put("Constanta", 8000000);

        for(String city : cities.keySet()) {
            System.out.println(city + " has " + cities.get(city) + " persons.");
        }

        cities.forEach((key, value) -> System.out.println(key + " has " + value + " persons"));
    }
}
