
public class Tab2 {

    public static void main(String[] args) {
        int[] tablouInt1 = new int[3];
        for (int i = 0; i < tablouInt1.length; i++) {
            System.out.print(tablouInt1[i] + "; ");
        }
        System.out.println("\nDimensiune tablou: " + tablouInt1.length);

        // adaugare elemente in tablou
        tablouInt1[0] = 2;
        tablouInt1[1] = 4;
        tablouInt1[2] = 1;
        // tablouInt1[3] = 6; // eroare de executie

        // Afisare elemente tablou
        System.out.println("\nTablou initializat:");
        for (int i = 0; i < tablouInt1.length; i++) {
            System.out.print(tablouInt1[i] + "; ");
        }
        // suprascrierea unui element din tablou
        tablouInt1[2] = 67;
        System.out.println("\nTablou cu elemente modificate:");
        for (int i = 0; i < tablouInt1.length; i++) {
            System.out.print(tablouInt1[i] + "; ");
        }
    }
}
