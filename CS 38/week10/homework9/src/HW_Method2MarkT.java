import java.awt.Color;
import java.awt.Font;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * A class that provides various utility functions, estimations, and 
 * demonstrations such as retail price calculation, paint job estimation, 
 * grade calculation, and drawing Olympic rings.
 * @author Mark Tikhonv
 * @version 0.0.1
 */
public class HW_Method2MarkT {
     private static Font defaultFont = new Font("Arial", Font.ITALIC, 32);
     private static int width = 400, height = 400;
     private static Color backgroundColor = Color.GRAY;
     private static Color textColor = new Color(58, 65, 74);
     private static Scanner scanner = new Scanner(System.in);
     private static Random random = new Random();
     private static Form defaultForm = new Form(
         width,
         height,
         backgroundColor,
         textColor,
         defaultFont,
         "Program by Mark Tikhonov"
     );


     /**
     * Calculates the retail price based on wholesale cost and markup percentage 
     * entered by the user, and displays the result using a graphical form.
     */
     public static void retailPriceCalculator(){
          System.out.print("Enter the wholesale cost: ");
          double wholesaleCost = Double.parseDouble(scanner.next());
          System.out.print("Enter the markup percentage: ");
          double markupPercentage = Double.parseDouble(scanner.next());
          double retailPrice = wholesaleCost + (wholesaleCost * markupPercentage / 100);
          System.out.printf("The retail price is %.2f\n", retailPrice);
          defaultForm.create().text(width / 2, height / 2, "The retail price is " + retailPrice);
     }

     /**
     * A nested class that estimates the cost of a paint job including gallons of 
     * paint, hours of labor, cost of materials, and labor charges.
     */
     public static class PaintJobEstimator{
          public PaintJobEstimator(){
               System.out.print("Enter the number of rooms: ");
               int rooms = scanner.nextInt();
               System.out.print("Enter price per gallon of pain: ");
               pricePerGallon = scanner.nextDouble();
               for (int i = 0; i < rooms; i++){
                    System.out.print("Enter the square footage of room " + (i + 1) + ": ");
                    roomsSF.add(scanner.nextDouble());
               }
          }

          /**
          * Calculates the number of gallons of paint required based on the 
          * square footage of rooms.
          * @return The number of gallons required.
          */
          public double gallondsOfPaintRequired(){
               double totalSF = 0;
               for (double sf : roomsSF){
                    totalSF += sf;
               }
               return totalSF / 115.0;
          }

          /**
          * Calculates the total hours of labor required based on the amount of paint needed.
          * @return The hours of labor required.
          */
          public double hoursOfLaborRequired(){
               return gallondsOfPaintRequired() * 8;
          }

          /**
          * Calculates the total cost of paint required.
          * @return The total paint cost.
          */
          public double costOfPaint(){
               return gallondsOfPaintRequired() * pricePerGallon;
          }

          /**
          * Calculates the labor charges based on hours of labor required.
          * @return The total labor charges.
          */
          public double laborCharges(){
               return hoursOfLaborRequired() * 18;
          }

          /**
          * Calculates the total cost of the paint job, including both paint 
          * and labor costs.
          * @return The total cost of the paint job.
          */
          public double totalCost(){
               return costOfPaint() + laborCharges();
          }

          /**
          * Displays an estimate of the paint job including gallons, labor hours, 
          * paint cost, labor charges, and total cost.
          */
          public void displayEstimate(){
               String gallons = String.format("Gallons of paint required: %.2f\n", gallondsOfPaintRequired());
               String hours = String.format("Hours of labor required: %.2f\n", hoursOfLaborRequired());
               String costPaint = String.format("Cost of paint: %.2f\n", costOfPaint());
               String labor = String.format("Labor charges: %.2f\n", laborCharges());
               String total = String.format("Total cost: %.2f\n", totalCost());
               var screen = defaultForm.create();
               screen.setFont(new Font("Arial", Font.PLAIN, 16));
               screen.text(width / 2, height / 2, gallons);
               screen.text(width / 2, height / 2 + 30, hours);
               screen.text(width / 2, height / 2 + 60, costPaint);
               screen.text(width / 2, height / 2 + 90, labor);
               screen.text(width / 2, height / 2 + 120, total);
     
               System.out.print(gallons);
               System.out.print(hours);
               System.out.print(costPaint);
               System.out.print(labor);
               System.out.print(total);
          }
          private List<Double> roomsSF = new ArrayList<Double>();
          private double pricePerGallon;
     }

     /**
     * Converts a temperature from Fahrenheit to Celsius.
     * @param f The temperature in Fahrenheit.
     * @return The temperature in Celsius.
     */
     public static double FtoC(double f){
          return (f - 32) * 5 / 9;
     }

     /**
     * Demonstrates the Fahrenheit-to-Celsius conversion by printing
     * conversions for temperatures from 0 to 20.
     */
     public static void demonstrateFtoC(){
          var screen = defaultForm.create();
          screen.setFont(new Font("Arial", Font.PLAIN, 16));
          for (int i = 0; i <= 20; i ++){
               String text = String.format("F: %d, C: %.2f", i, FtoC(i));
               screen.text(width / 2, 10 + i * screen.getFont().getSize(), text);
               System.out.println(text);
          }
     }

     /**
     * Calculates the average of any number of grades provided as input.
     * @param grades A variable number of integer grades.
     * @return The average of the grades.
     */
     public static double calcAverage(int ...grades){
          double sum = 0;
          for (int i = 0; i < grades.length; i++){
               sum += grades[i];
          }
          return sum / grades.length;
     }

     /**
     * Determines the letter grade based on a given test score.
     * @param testScore The score of the test.
     * @return The corresponding letter grade.
     */
     public static char determineGrade(int testScore){
          if (testScore >= 90)
               return 'A';
          else if (testScore >= 80)
               return 'B';
          else if (testScore >= 70)
               return 'C';
          else if (testScore >= 60)
               return 'D'; 
          return 'F'; 
     }

     /**
     * Prompts the user to enter five test scores, determines the letter grade for 
     * each score, and displays the result both in the console and on a graphical form.
     */
     public static void displayGrade(){
          var scores = new int[5];
          var screen = defaultForm.create();
          int i;
          screen.setFont(new Font("Arial", Font.PLAIN, 16));
          for (i = 0; i < 5; i++){
               System.out.print("Enter test score " + (i + 1) + ": ");
               scores[i] = Integer.parseInt(scanner.next());
          }
         
          for (i = 0; i < 5; i++){
               String out = String.format("Test score %d: %d, Grade: %c", i + 1, scores[i], determineGrade(scores[i]));
               System.out.println(out);
               screen.text(width / 2, height / 2 + i * screen.getFont().getSize(), out);
          }
          System.out.println("Average: " + calcAverage(scores));
          screen.text(width / 2, height / 2 + i * screen.getFont().getSize(), "Average: " + calcAverage(scores));
     }

     /**
     * Generates a random color using RGB values, each between 0 and 255.
     * @return A randomly generated Color object.
     */
     public static Color randomColor(){
          return new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256));
     }

     /**
     * Displays the title "Paris Olympics" along with the author's signature on a 
     * graphical screen at specified coordinates.
     * @param screen The graphical screen to draw on.
     * @param x The x-coordinate for the title.
     * @param y The y-coordinate for the title.
     */
     public static void title(Draw screen, double x, double y){
          screen.text(x, y, "Paris Olympics");
          screen.text(x, y + screen.getFont().getSize(), "By Mark 10/25");
     }

     /**
     * Draws a ring with the specified center coordinates and radius, using 
     * randomly generated colors.
     * @param screen The graphical screen to draw on.
     * @param x The x-coordinate of the ring's center.
     * @param y The y-coordinate of the ring's center.
     * @param radius The radius of the ring.
     */
     public static void drawRing(Draw screen, double x, double y, double radius){
          screen.setPenColor(randomColor());
          for (int i = 0; i < 7; i++){
               screen.circle(x, y, radius - i);
          }
     }

     /**
     * Demonstrates drawing the Olympic rings with titles and random colors on a 
     * graphical form.
     */
     public static void testOlympicsMark(){
          var screen = defaultForm.create();
          screen.setFont(new Font("Arial", Font.PLAIN, 16));
          title(screen, width / 4, height / 2);
          drawRing(screen, 50, 275, 30);
          drawRing(screen, 110, 275, 30);
          drawRing(screen, 170, 275, 30);
          drawRing(screen, 80, 310, 30);
          drawRing(screen, 140, 310, 30);
     }
     public static void main(String []args){
          // retailPriceCalculator();
          // new PaintJobEstimator().displayEstimate();
          // demonstrateFtoC();
          // displayGrade();
          testOlympicsMark();     
     }
}
