import java.util.Scanner;
import java.util.Vector;

public class VecOrg {
    public static void main(String[] args) {
        Scanner Input = new Scanner(System.in);

        Vector<Integer> Pare = new Vector<Integer>();
        Vector<Integer> Impare = new Vector<Integer>();

        int n = Input.nextInt();
        int num = 0;
        for (int i = 0; i < n; i++) {
            num = Input.nextInt();

            if (num % 2 == 0) {
                Pare.add(num);
            } else {
                Impare.add(num);
            }
        }

        System.out.println("Pare: " + Pare.toString());
        System.out.println("Impare: " + Impare.toString());
    }
}
