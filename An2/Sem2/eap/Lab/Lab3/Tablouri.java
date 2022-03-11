import java.util.Arrays;

public class Tablouri {
    int alMeuPrimitiv;

    public static void main(String[] args) {
        int[] tablouInt1 = { 1, 3, 4, 5 };
        int[] tablouInt2 = new int[] { 9, 8, 7 };

        for (int i = 0; i < tablouInt1.length; i++)
            System.out.print(tablouInt1[i] + " ");

        System.out.println("");
        for (int i = 0; i < tablouInt2.length; i++)
            System.out.print(tablouInt2[i] + " ");

        Tablouri test = new Tablouri();
        System.out.println("\ntest " + test.alMeuPrimitiv);

        System.out.println("");
        int[] tablouInt3 = new int[3];
        for (int i = 0; i < tablouInt3.length; i++)
            System.out.print(tablouInt3[i] + " ");

        System.out.println();
        // ArrayList<Integer> testArr = new ArrayList<Integer>();
        int[] t = new int[20];
        Arrays.fill(t, 10);
        Arrays.fill(t, 10, 20, 9);
        System.out.println(Arrays.toString(t));

        Arrays.sort(t);
        System.out.println(Arrays.toString(t));

    }
}