import java.util.Scanner;
import java.util.Random;
import java.awt.Font;
/**
 * Description: fixing the errors code
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class TestResults
{
    //replace qqq, 1234 and _____
    public static void letterGrade( ) //pg 134
    {
        // Variable to hold the numeric test score
        int qqq;

        // Create a Scanner object for keyboard input.
        // ________________
        
        Scanner keyboard = new Scanner(System.in);

        // Get the numeric test score.
        System.out.print("Enter your numeric test score: ");
        int testScore = keyboard.nextInt();

        // Display the grade.
        if (testScore < 60)
        {
            System.out.println("Your grade is F.");
        }
        else
        {
            if (testScore < 70)
            {
                System.out.println("Your grade is D.");
            }
            else
            {
                if (testScore < 80)
                {
                    System.out.println("Your grade is C.");
                }
                else
                {
                    if (testScore < 90)
                    {
                        System.out.println("Your grade is B.");
                    }
                    else
                    {
                        System.out.println("Your grade is A.");
                    }
                }
            }
        }
    }
    public static void main(String []args){
        letterGrade();
    }
}
