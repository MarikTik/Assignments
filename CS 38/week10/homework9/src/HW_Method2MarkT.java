import java.awt.Color;
import java.awt.Font;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class HW_Method2MarkT {
     private static Font defaultFont = new Font("Arial", Font.ITALIC, 32);
     private static int width = 400, height = 400;
     private static Color backgroundColor = new Color(176, 196, 222);
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



     public static void retailPriceCalculator(){
          System.out.print("Enter the wholesale cost: ");
          double wholesaleCost = Double.parseDouble(scanner.next());
          System.out.print("Enter the markup percentage: ");
          double markupPercentage = Double.parseDouble(scanner.next());
          double retailPrice = wholesaleCost + (wholesaleCost * markupPercentage / 100);
          System.out.printf("The retail price is %.2f\n", retailPrice);
          defaultForm.create().text(width / 2, height / 2, "The retail price is " + retailPrice);
     }

     public static class PaintJobEstimator{
          public PaintJobEstimator(){
               System.out.print("Enter the number of rooms: ");
               int rooms = scanner.nextInt();
               System.out.print("Enter price per gallon of pain");
               pricePerGallon = scanner.nextDouble();
               for (int i = 0; i < rooms; i++){
                    System.out.print("Enter the square footage of room " + (i + 1) + ": ");
                    roomsSF.add(scanner.nextDouble());
               }
          }
          public double gallondsOfPaintRequired(){
               double totalSF = 0;
               for (double sf : roomsSF){
                    totalSF += sf;
               }
               return totalSF / 115.0;
          }
          public double hoursOfLaborRequired(){
               return gallondsOfPaintRequired() * 8;
          }
          public double costOfPaint(){
               return gallondsOfPaintRequired() * pricePerGallon;
          }
          public double laborCharges(){
               return hoursOfLaborRequired() * 18;
          }
          public double totalCost(){
               return costOfPaint() + laborCharges();
          }
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
               screen.setFont();
          }
          public double FtoC(double f){
               return (f - 32) * 5 / 9;
          }
          public void demonstrateFtoC(){
               var screen = defaultForm.create();
               screen.setFont(new Font("Arial", Font.PLAIN, 16));
               for (int i = 0; i <= 20; i ++){
                    String text = String.format("F: %d, C: %.2f", i, FtoC(i));
                    screen.text(width / 2, 10 + i * screen.getFont().getSize(), text);
                    System.out.println(text);
               }
          }
          private List<Double> roomsSF = new ArrayList<Double>();
          private double pricePerGallon;
         
     }

     // will accept any number of grades, 5 included
     public static double calcAverage(int ...grades){
          double sum = 0;
          for (int i = 0; i < grades.length; i++){
               sum += grades[i];
          }
          return sum / grades.length;
     }

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
     public static void displayGrade(){
          var scores = new int[5];
          var screen = defaultForm.create();
          screen.setFont(new Font("Arial", Font.PLAIN, 16));
          for (int i = 0; i < 5; i++){
               System.out.print("Enter test score " + (i + 1) + ": ");
               scores[i] = Integer.parseInt(scanner.next());
          }
          for (int i = 0; i < 5; i++){
               String out = String.format("Test score %d: %d, Grade: %c", i + 1, scores[i], determineGrade(scores[i]));
               System.out.println(out);
               screen.text(width / 2, height / 2 + i * screen.getFont().getSize(), out);
          }
     }

     public static Color randomColor(){
          return new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256));
     }

     public static void title(Draw screen, double x, double y){
          screen.text(x, y, "Paris Olympics");
          screen.text(x, y + screen.getFont().getSize(), "By Mark 10/25");
     }

     public static void drawRing(Draw screen, double x, double y, double radius){
          screen.setPenColor(randomColor());
          for (int i = 0; i < 7; i++){
               screen.circle(x, y, radius - i);
          }
     }

     public static void testOlympicsMark(){
          var screen = defaultForm.create();
          screen.setFont(new Font("Arial", Font.PLAIN, 16));
          title(screen, width / 4, height / 2);
          drawRing(screen, 50, 275, 45);
          drawRing(screen, 100, 275, 45);
          drawRing(screen, 150, 275, 45);
          drawRing(screen, 75, 300, 45);
          drawRing(screen, 125, 300, 45);
     }
     public static void main(String []args){
          // retailPriceCalculator();
          // new PaintJobEstimator().displayEstimate();
          // demonstrateFtoC();
          // displayGrade();
           testOlympicsMark();     
     }
}
