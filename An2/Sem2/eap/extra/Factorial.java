import java.util.Scanner;

public class Factorial {
    public static void main(String[] args) {
        Scanner Input = new Scanner(System.in);
        int num = Input.nextInt();

        int fact = 1;
        for (int i = 1; i <= num; i++) {
            fact *= i;
        }

        System.out.println(num + " factorial is " + fact);
    }
}
