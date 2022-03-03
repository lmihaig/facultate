import java.util.Scanner;

public class Numpar {
    public static void main(String[] args) {
        Scanner Scan = new Scanner(System.in);
        int high = Scan.nextInt();

        for (int i = 0; i <= high; i++)
            if (i % 2 == 0)
                System.out.print(i + " ");
    }
}