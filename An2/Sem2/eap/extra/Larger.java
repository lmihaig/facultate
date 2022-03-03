import java.util.Scanner;

public class Larger {
    public static void main(String[] args) {
        Scanner Input = new Scanner(System.in);
        int firstNum = Input.nextInt();
        int secondNum = Input.nextInt();

        int larger = (firstNum > secondNum) ? firstNum : secondNum;
        System.out.println("Larger: " + larger);
    }
}
