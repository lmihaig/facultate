import java.util.Scanner;

public class Medie {
    public static void main(String[] args) {
        Scanner Input = new Scanner(System.in);

        int sum = 0;
        int num = 0;
        int n = Input.nextInt();

        while (n != -1) {
            sum += n;
            num++;
            n = Input.nextInt();
        }

        System.out.println("Media este " + (sum / num));
    }
}
