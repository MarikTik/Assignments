//import java.util.Scanner;
import java.awt.Font;
import java.util.Scanner;
/**
 * Description
 * class with all the required methods from homework 3 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class HW3MarkTikhonov {

    // // range 1 - 10
    public static int romanNumeralToNumber(String numeral){
        switch (numeral) {
            case "I": return 1;
            case "II": return 2;
            case "III": return 3;
            case "IV": return 4;
            case "V": return 5;
            case "VI": return 6;
            case "VII": return 7;
            case "VIII": return 8;
            case "IX": return 9;
            case "X": return 10;
        }
        return -1;
    }
    
    // this interface will be used as a placeholder for lambda expressions of the form T expression(T val1, T val2)
    // so that everything that looks like it will fit nicely.
    interface Comparator<T>{
        public boolean compare(T val1, T val2); // if val1 should remain in place, returns true, otherwise false
    }

    // O(n^2) sort method that should work with any array as long as a comparator functor is supplied
    // I am by no means a java programmer but that's how I would strive to implement it in any other language
    // I know.
    public static <T> void sortArray(T []array, Comparator<T> comparator){
        for (int i = 0; i < array.length; i++)
            for (int j = i + 1; j < array.length; j++)
                if (!comparator.compare(array[i], array[j])){
                    T temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
    }

    // finds the index of an item in a given array
    // requires T to be a numeric type, otherwise undefined behavior (or depends on the rules I don't know yet)
    // if the item is not in the array, returns -1
    // *** I am wondering if I can limit the scope of T in practice...
    public static <T> int indexOf(T []array, T target){
        for (int i = 0; i < array.length; i++)
            if (array[i] == target)
                return i;
        return -1;
    }

    public static void romanNumerals(){
        System.out.print("Enter roman numeral in the range of 1-10 (I - X): ");
        Scanner scanner = new Scanner(System.in);
        String numeral = scanner.nextLine();

        int result = switch(numeral){
            case "I" -> 1;
            case "II" -> 2;
            case "III" -> 3;
            case "IV" -> 4;
            case "V" -> 5;
            case "VI" -> 6;
            case "VII" -> 7;
            case "VIII" -> 8;
            case "IX" ->  9;
            case "X" -> 10;

            default -> -1;
        };
        if (result == -1) System.out.println("Error: Numeral is not in range 1 - 10");
        else System.out.printf("%s = %d\n", numeral, result);
        scanner.close();
    }

    public static void sortedNames(){
        Scanner scanner = new Scanner(System.in);
        String[] names = new String[3];
        System.out.println("Enter three names to be sorted in ascending order: ");
        
        for (int i = 0; i < 3; i++)
            names[i] = scanner.next();
        
        sortArray(names, (name1, name2) -> name1.compareTo(name2) < 0); 
        // amazing that it works even though I gave a pretty random name for the interface method "compare"
        // apparently for this kind of interface only the signature matters and not the name, 
        // my guess is that it is true only for interfaces with one method, though I may be wrong.

        for (var name : names)
            System.out.println(name);

        scanner.close();
        // echo "Charlie Leslie Andy" | java week4/homework3/src/HW3MarkTikhonov.java
    }

    public static void runningTheRace(){
        String []horsemen = new String[3];
        double []raceTimes = new double[3];
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter horseman racers names and the time it took tham to complete the race in the format: [name] [time]");
        for(int i = 0; i < 3; i++){
            horsemen[i] = scanner.next();
            raceTimes[i] = scanner.nextDouble();
        }
        // please take into account that I am relying purely on my experience with C# and other languages, 
        // It's the code I have written after clarifying some of my assumptions on the internet (no AI used).

        sortArray(horsemen, (horseman1, horseman2) -> { 
            int index1 = indexOf(horsemen, horseman1);
            int index2 = indexOf(horsemen, horseman2);

            return raceTimes[index1] < raceTimes[index2];
        });
        
        for (int i = 0; i < 3; i++){
            System.out.printf("%d. %s\n", i + 1, horsemen[i]);
        }
        
        //echo "Charlie 3 Leslie 10 Andy 1" | java week4/homework3/src/HW3MarkTikhonov.java
        scanner.close();
    }


    public static void main(String []args){
        //romanNumerals();
        sortedNames();
        //runningTheRace();
        
        // Draw screen = new Draw();
        // screen.setCanvasSize(400, 400);
        // screen.setXscale(0, 400);
        // screen.setYscale(400, 0);
        // screen.clear(Draw.GRAY);
        // screen.setPenColor(Draw.BLACK);
        // screen.drawLine(0, 0, 400, 400);
    }
}   

