//import java.util.Scanner;
import java.awt.Font;
import java.util.Scanner;
import java.util.Random;
import java.awt.Color;
/**
 * Description
 * class with all the required methods from homework 3 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class HW3MarkTikhonov {

   /**
     * Description
     * encapsulates some of the setup settings for Draw object screens
     * 
     * @author Mark Tikhonov
     * @version 0.0.1
     */

    private static final Random rand = new Random();

    static class ScreenSettings{
        public int width;
        public int height;
        public Color backgroundColor;
        public Color penColor;
        public Font font;
        public String title;
   
        public ScreenSettings(int width, int height, Color backgroundColor, Color penColor, Font font, String title){
            this.width = width;
            this.height = height;
            this.backgroundColor = backgroundColor;
            this.penColor = penColor;
            this.font = font;
            this.title = title;
        }
    }

   
    public static Draw standardScreen(ScreenSettings settings){
        Draw screen = new Draw();

        //scaling the screen
        screen.setCanvasSize(settings.width, settings.height);
        screen.setXscale(0, settings.width);
        screen.setYscale(settings.height, 0);
        screen.setTitle(settings.title);
        screen.clear(settings.backgroundColor);
        
        // write my name in the bottom under random orientation
        screen.setFont(new Font("Serif", Font.ITALIC, 32));
        screen.setPenColor(Draw.PINK);
        screen.text(
            settings.width / 2,
            settings.height - screen.getFont().getSize() * 2,
            "Mark Tikhonov",
            rand.nextInt(-40, 40)
        );

        screen.setPenColor(Draw.BLACK);  
        screen.setFont(settings.font);  
        //screen.text(halfWidth, nameFont.getSize(), "Mark Tikhonov", rotation);

        //drawing delimter lines as a proof of concept
        screen.line(settings.width / 2, settings.height, settings.width / 2, 0);
        screen.line(0, settings.height / 2, settings.width, settings.height / 2);
        
        screen.setPenColor(settings.penColor);


        return screen;
    }

    public static Draw writeLines(Draw screen, int x, int y, String []lines){
        int yOffset = screen.getFont().getSize();
        y += yOffset;
        for (var line : lines){ // I have seen this in the quiz so it's reasonable to use it
             screen.textLeft(x, y, line);
             y += yOffset;
        }

        return screen;
    }

    // accepts newlines as a way to split a single line into pieces
    public static Draw writeLine(Draw screen, int x, int y, String line){
        writeLines(screen, x, y, line.split("[\n]"));
        return screen;
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
        Draw screen = standardScreen(
            new ScreenSettings(
                400,
                400,
                Draw.GRAY,
                Draw.RED, 
                new Font("Serif", Font.BOLD, 24),
                "romanNumerals by Mark Tikhonov"
        ));

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
        if (result == -1) {
            System.out.println("Error: Numeral is not in range 1 - 10");
            writeLine(screen, 16, 16, "Error:\nNumeral is\nnot in \nrange\n1-10");
        }
        else {
            System.out.printf("%s = %d\n", numeral, result);
            screen.textLeft(16, 16, numeral + " = " + result);
        }
        scanner.close();
    }

    public static void sortedNames(){
        Scanner scanner = new Scanner(System.in);
        String[] names = new String[3];
        Draw screen = standardScreen(
            new ScreenSettings(
                400,
                400,
                Draw.GRAY,
                Draw.RED, 
                new Font("Helvetica", Font.BOLD, 24),
                "sortedNames by Mark Tikhonov"
        ));

        System.out.println("Enter three names to be sorted in ascending order: ");
        
        for (int i = 0; i < 3; i++)
            names[i] = scanner.next();
        
        sortArray(names, (name1, name2) -> name1.compareTo(name2) < 0); 
        // amazing that it works even though I gave a pretty random name for the interface method "compare"
        // apparently for this kind of interface only the signature matters and not the name, 
        // my guess is that it is true only for interfaces with one method, though I may be wrong.

        for (var name : names)
            System.out.println(name);
        writeLines(screen, 16, 16, names);
        scanner.close();
    }

    public static void runningTheRace(){
        String []horsemen = new String[3];
        double []raceTimes = new double[3];
        Scanner scanner = new Scanner(System.in);
        Draw screen = standardScreen(
            new ScreenSettings(
                400,
                400,
                Draw.GRAY,
                Draw.RED, 
                new Font("Ariel", Font.BOLD, 24),
                "runningTheRace by Mark Tikhonov"
        ));

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
        writeLines(screen, 16, 16, new String[]{
            "1. " + horsemen[0],
            "2. " + horsemen[1],
            "3. " + horsemen[2]
        });
        scanner.close();
    }


    public static void main(String []args){
        romanNumerals();
        //sortedNames();
        //runningTheRace();
        
        
    }
}   

