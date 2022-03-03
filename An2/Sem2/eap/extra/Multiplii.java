import java.util.Scanner;

public class Multiplii {
    public static void main(String[] args) {
        Scanner Input = new Scanner(System.in);
        int numar = Input.nextInt();
        int sum = 0;
        for (int i = 0; i <= numar; i++) {
            if (i % 15 == 0)
                sum += i;
        }

        System.out.println("Suma: " + sum);
    }

}
