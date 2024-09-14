//import java.util.Scanner;
import java.awt.Font;
import java.util.Scanner;
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

    /**
    * returns a standardized screen form employing a given set settings.
    *
    * @param settings the desired settings that the screen should abide by
    * @return Draw object with the given settings
    */
    public static Draw standardScreen(ScreenSettings settings){
        Draw screen = new Draw();

        //scaling the screen
        screen.setCanvasSize(settings.width, settings.height); 
        screen.setXscale(0, settings.width);
        screen.setYscale(settings.height, 0);
        screen.setTitle(settings.title);
        screen.clear(settings.backgroundColor);

        screen.setPenColor(Draw.BLACK);  
        screen.setFont(settings.font);  
     
    
        screen.line(settings.width / 2, settings.height, settings.width / 2, 0); // draws a cross separating the screen into 
        screen.line(0, settings.height / 2, settings.width, settings.height / 2); // 4 sections
        
        screen.setPenColor(settings.penColor);
        return screen;
    }

    /**
     * writes an array of lines separated by vertical jumps on the screen canvas starting from (x, y)
     * writes from top to bottom
     * 
     * @param screen the screen object to write lines on 
     * @param x left horizontal coordinate for the beginning of the text
     * @param y left vertical coordinate for the beginning of the text
     * @param lines an array of strings to print on the canvas 
     * @return none
     */
    public static void writeLines(Draw screen, int x, int y, String []lines){
        int yOffset = screen.getFont().getSize(); 
        y += yOffset;
        for (var line : lines){ // I have seen this in the quiz so it's reasonable to use it
             screen.textLeft(x, y, line);
             y += yOffset;
        }
    }

    /**
     * writes a string on the screen canvas respecting newline characters "\n" in the given string
     * @param screen the screen object to write lines on 
     * @param x left horizontal coordinate for the beginning of the text
     * @param y left vertical coordinate for the beginning of the text
     * @param line the string to print on canvas
     * @return none
     *
     */
    public static void writeLine(Draw screen, int x, int y, String line){
        writeLines(screen, x, y, line.split("[\n]"));
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
                if (!comparator.compare(array[i], array[j])){ // for any pair of elements, if the comparator returns false, swap them
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
        String numeral = scanner.next(); // taking only the next token so that to limit user errors
        Draw screen = standardScreen( // setting my screen
            new ScreenSettings(
                400,
                400,
                Draw.GRAY,
                Draw.RED, 
                new Font("Serif", Font.BOLD, 24),
                "romanNumerals by Mark Tikhonov"
        ));
        // switch statement as shown in the book, maps the strings to return values and assignes to result
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
        if (result == -1) { // if there was a mistake, notify the user
            System.out.println("Error: Numeral is not in range 1 - 10");
            writeLine(screen, 16, 16, "Error:\nNumeral is\nnot in \nrange\n1-10");
        }
        else { // if everything is good, output the translation of the roman numeral to the console/graphics screen
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
        // iterating to scan all the names into an array, this is better because I can change the amount of names 
        // in the function as I desire.
        for (int i = 0; i < names.length; i++)
            names[i] = scanner.next();
        
        // this came from more functional based approach which might be foreign to Java's OOP structure
        // the idea is that for each pair of names, I am going to comapre them and if the function (which
        // here is represented by an anonymous lambda) returns false, the sortArray method swaps any two names
        // in this way I can sort by any desired property at my whim, which is much more convenient.
        sortArray(names, (name1, name2) -> name1.compareTo(name2) < 0); 

        // amazing that it works even though I gave a pretty random name for the interface method "compare"
        // apparently for this kind of interface only the signature matters and not the name, 
        // my guess is that it is true only for interfaces with one method, though I may be wrong.

        for (int i = 0; i < names.length; i++){
            names[i] = (i + 1) + ". " + names[i]; // adding positional identifiers to the name
            System.out.println(names[i]);
           
        }  
            
        writeLines(screen, 16, 16, names); // outputing the ordered array on the graphics screen
        scanner.close(); // not forget to clean the mess...
    }

    public static void runningTheRace(){
        //here I select a simillar approach as in the previous method, this time with two arrays
        int horsemenNumber = 3;
        String []horsemen = new String[horsemenNumber];
        double []raceTimes = new double[horsemenNumber];
        Scanner scanner = new Scanner(System.in);
        Draw screen = standardScreen( // setting my screen
            new ScreenSettings(
                400,
                400,
                Draw.GRAY,
                Draw.RED, 
                new Font("Ariel", Font.BOLD, 24),
                "runningTheRace by Mark Tikhonov" 
        ));

        System.out.println("Enter horseman racers names and the time it took tham to complete the race in the format: [name] [time]");
        // iterates over the minimum size of the two arrays, here they should have
        // length of 3, but if I will decide to change one and forget the other, I will be
        // shielded from an out of bounds error.
        for(int i = 0; i < Math.min(horsemen.length, raceTimes.length); i++){
            horsemen[i] = scanner.next();
            raceTimes[i] = scanner.nextDouble();
        }

        // this has a simillar idea as what I used in the previous function.
        // Though it looks complext, it really isn't, what it does is sort by the
        // position of the racer in the raceTimes array, the position is exactly
        // the index of a given horseman at reflected in the raceTimes array.
        // This method call illustrates this concept.
        sortArray(horsemen, (horseman1, horseman2) -> { 
            int index1 = indexOf(horsemen, horseman1);
            int index2 = indexOf(horsemen, horseman2);

            return raceTimes[index1] < raceTimes[index2];
        });
        
        for (int i = 0; i < horsemen.length; i++){ // iterate over the sorted horsemen list and output the positions
            System.out.printf("%d. %s\n", i + 1, horsemen[i]);
        }
        writeLines(screen, 16, 16, new String[]{ // print the positions of the first 3 horsemen
            "1. " + horsemen[0], // this satisfies the requirements of the assignment, however if another number would be
            "2. " + horsemen[1], // chosen, it would be problematic, for n > 3 the program would show only 3 names but 
            "3. " + horsemen[2] // for n < 3, the program would crash 
        });
        scanner.close(); // cleaning again...
    }


    public static void main(String []args){
        //romanNumerals();
        sortedNames();
        //runningTheRace();
        
        
    }
}   

