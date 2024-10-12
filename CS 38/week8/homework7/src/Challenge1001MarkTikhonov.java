import java.awt.Font;
import java.awt.Color;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.File;
import java.io.IOException;
/**
* Description
* challanges from honework 7
* 
* @author Mark Tikhonov
* @version 0.0.1
*/
public class Challenge1001MarkTikhonov
{
    private static int width = 400, height = 400;
 
    private static final Font bigFont = new Font("Arial", Font.BOLD, 32);
    private static final Font mediumFont = new Font("Serif", Font.BOLD, 16);
    private static final Font smallFont = new Font("Serif", Font.BOLD, 8);

    private static Form defaultForm = new Form(
          width,
          height,
          Draw.BLACK,
          new Color(39, 215, 74),
          bigFont, 
          "challenge assignment ;)"
    );
    
    
    public static void sumOfNumbers(){
        var screen = defaultForm.create();
        screen.setFont(mediumFont);
        Scanner scanner = new Scanner(System.in);
        int sum = 0;
        System.out.print("Enter a number: ");
        int n = Integer.parseInt(scanner.next());
        for (int i = 1; i <= n; i++)
             sum += i;
        System.out.println("Sum of numbers from 1 to " + n + " is " + sum);
        screen.text(200, 200, "Sum of numbers from 1 to " + n + " is ");
        screen.text(200, 220, Integer.toString(sum));
        scanner.close();
   }
   public static void letterCounter(){
        var screen = defaultForm.create();
        screen.setFont(mediumFont);
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a string: ");
        String str = scanner.nextLine();
        System.out.print("Enter a character: ");
        char c = scanner.next().charAt(0);
        int count = 0;
        for (int i = 0; i < str.length(); i++)
            if (str.charAt(i) == c)
                count++;
        System.out.println("Number of letters in the string: " + count);
        screen.text(200, 200, "Number of letters in the string: " + count);
        scanner.close();
   }
   public static void fileHeadDisplay() throws IOException{
        var screen = defaultForm.create();
        screen.setFont(mediumFont);
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a file name: ");
        String fileName = scanner.nextLine();
        int n = 5;
        
        File file = new File(fileName);
        Scanner fileScanner = new Scanner(file);
        for (int i = 0, y= 20; i < n; i++, y+=20) {
             String line = fileScanner.nextLine();
             screen.text(200, y, line);
             System.out.println(line);
        }
        fileScanner.close(); 
        scanner.close();
   }
    //Read a string from the keyboard and print the characters in 
    //reversed order on a black graphics screen. For example entering 
    //"Irvine Valley College" displays "egelloC yellaV enivrI" in large
    //fonts. Choose an RGB color, not one of the default colors that 
    //can contrast well on the black background. You must have your name 
    //on the title bar and somewhere else on the screen.
    public static void reverseMe( )
    {
        var screen = defaultForm.create();
        var scanner = new Scanner(System.in);
        System.out.print("Enter a string: ");
        String line = scanner.nextLine();
        String reversed = ""; // could be optimized with a charr array

        for (int i = line.length() - 1; i >= 0; i--)
            reversed += line.charAt(i);
        
        System.out.printf("reversed: %s\n", reversed);
        FormWriter.writeLines(screen, 100, 20, reversed.split("\\s+"));
        scanner.close();
    }

    //Read a start integer from the keyboard between 10 and 30. 
    //Read an end  integer from the keyboard between 45 and 55. 
    //Use a while loop to validate numbers are in the correct range
    //as described in your textbook.
    //Print on the terminal and graphics screen all integers between
    //start and end. Use a new font you haven't used before.
    public static void startToEnd( )
    {
        var screen = defaultForm.create();
        var scanner = new Scanner(System.in);
        screen.setFont(smallFont);
        String errorMessage = "error: number not in range";
        // ill written directions: no specification about what should 
        // happen if validation fails, moreover, validation of ranges is done 
        // with if statements and not loops.
        System.out.print("Enter number between 10 and 30: ");
        int start = scanner.nextInt();
        if (10 > start || start > 30){
            System.out.println(errorMessage);
            FormWriter.writeLine(screen, 10, 20, errorMessage);
            scanner.close();
            return;
        }
        System.out.print("Enter number between 45 and 55: ");
        int end = scanner.nextInt();
        if (45 > end || end > 55){
            System.out.println(errorMessage);
            FormWriter.writeLine(screen, 10, 20, errorMessage);
            scanner.close();
            return; 
        }
        String []buffer = new String[end - start + 1];
        int i = 0;
        while (start <= end){
            buffer[i ++] = "" + start;
            System.out.println(start++);
        }
        FormWriter.writeLines(screen, 200, 10, buffer);
        scanner.close();
        
    }

    //Same as above but write the numbers into a file "startToEndYName.txt"
    public static void fileWriteStartToEnd() throws IOException
    {
        var screen = defaultForm.create();
        var scanner = new Scanner(System.in);
        screen.setFont(smallFont);
        String errorMessage = "error: number not in range";
        PrintWriter writer = new PrintWriter("startToEndMark.txt");
        
        System.out.print("Enter number between 10 and 30: ");
        int start = scanner.nextInt();
        if (10 > start || start > 30){
            System.out.println(errorMessage);
            FormWriter.writeLine(screen, 10, 20, errorMessage);
            scanner.close();
            writer.close();
            return;
        }
        System.out.print("Enter number between 45 and 55: ");
        int end = scanner.nextInt();
        if (45 > end || end > 55){
            System.out.println(errorMessage);
            FormWriter.writeLine(screen, 10, 20, errorMessage);
            scanner.close();
            writer.close();
            return; 
        }
        String []buffer = new String[end - start + 1];
        int i = 0;
        while (start <= end){
            buffer[i ++] = "" + start;
            writer.println(start++);

        }
        FormWriter.writeLines(screen, 200, 10, buffer);
        writer.close();
        scanner.close();
    }
    
    //Read the file studentByYName.txt and print only the name and
    //GPA of students who between 2.00 and 2.99 gpa
    public static void fileCstudents() throws IOException
    {
        // I generally consider it more interesting to write descriptive code 
        // and while I understand that loops with indexOf() are important,
        // I think that I learn more if I use something I haven't seen before
        // or haven't used a long time. Data fitering and manipulation with loops and if statements
        // is as good as eating soup with a fork, and since the method directions
        // above didn't restrict me, I reserve the right to use a spoon.
        var screen = defaultForm.create();
        screen.setFont(mediumFont);
        var students = Student.fromFile("week8/lecture2/data.txt"); // I had the students text file by this path
        // if you would like to rerun it use "studentByYName.txt" instead

        students.stream()
            .filter(student -> 2.0 <= student.GPA && student.GPA <= 2.99) // filter all the student objects with the right gpa
            .forEach(student -> 
                {   
                    String out = String.format("%s\tGPA: %.2f", student.name, student.GPA);
                    System.out.println(out);
                    FormWriter.writeCenterAutoShifted(screen, width, height, out); 
                    // I use this method because I can't influence counters from outer scope so I have to resort to static method behavior
                }); // print the (name    GPA) strings of the students
            FormWriter.resetShifter(); // reset the shifter so if I reuse the method it doesn't start from the last position
    }
    public static void main(String[] args)
    {
        // book prolems
        //////////////////////////////////////////
        //sumOfNumbers();
        // letterCounter();
        // try{
        //     fileHeadDisplay();
        // }
        // catch(IOException ex){
        //     System.out.println(ex.getMessage());
        // }
        // //////////////////////////////////////////
        // // challenge problems
        // //////////////////////////////////////////
        // reverseMe();
        // startToEnd();
        // try{
        //     // fileWriteStartToEnd();
        //     // fileCstudents();
        // }
        // catch(IOException ex){
        //     System.out.println(ex.getMessage());
        // }
        //////////////////////////////////////////
    }
}
