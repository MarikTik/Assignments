//import java.util.Scanner;
import java.awt.Font;

/**
 * Description
 * class with all the required methods from homework 3 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class HW3MarkTikhonov {

    // // range 1 - 10
    // public static int romanNumeralToNumber(String numeral){
    //     switch (numeral) {
    //         case "I": return 1;
    //         case "II": return 2;
    //         case "III": return 3;
    //         case "IV": return 4;
    //         case "V": return 5;
    //         case "VI": return 6;
    //         case "VII": return 7;
    //         case "VIII": return 8;
    //         case "IX": return 9;
    //         case "X": return 10;
    //     }
    //     return -1;
    // }
    // public static void romanNumerals(){
    //     System.out.print("Enter roman numeral in the range of 1-10 (I - X): ");
    //     Scanner scanner = new Scanner(System.in);
    //     String numeral = scanner.nextLine();
    //     int result = romanNumeralToNumber(numeral);
    //     if (result == -1) System.out.println("Error: Numeral is not in range 1 - 10");
    //     else System.out.println(numeral + " = " + result);
    //     scanner.close();
    // }


    public static void main(String []args){
        //romanNumerals();
        Draw screen = new Draw();
        screen.setCanvasSize(400, 400);
        screen.setXscale(0, 400);
        screen.setYscale(400, 0);
        screen.clear(Draw.GRAY);
        screen.setPenColor(Draw.BLACK);
        screen.drawLine(0, 0, 400, 400);
    }
}   

