import java.util.Scanner;

public class ChargeAccountValidator {
    private static final int[] validAccountNumbers = new int[]{
        5658845, 4520125, 7895122, 8777541, 8451277, 1302850,
        8080152, 4562555, 5552012, 5050552, 7825877, 1250255,
        1005231, 6545231, 3852085, 7576651, 7881200, 4581002
    };

    public boolean isValid(int accountNumber){
        for (int val : validAccountNumbers)
            if (val == accountNumber)
                return true;
        return false;
    }

    public static void demo(){
        var validator = new ChargeAccountValidator();
        var stream = new Scanner(System.in);
        System.out.print("Enter account number: ");
        var number = stream.nextInt();
        if (validator.isValid(number))
            System.out.println("The account number is valid");
        
        else 
            System.out.println("The account number is invalid");
        stream.close();
    }
}
