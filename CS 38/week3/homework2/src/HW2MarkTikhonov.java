import java.util.Scanner;
import java.awt.Color;
import java.awt.Font;


/**
 * Description
 * class with all the required methods from homework 2 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class HW2MarkTikhonov {

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
     
     // adding some basic figures for easy access when creating screens
     private final static Font textFont = new Font("Arial", Font.PLAIN, 16);
     private final static Font nameFont = new Font("Arial", Font.BOLD, 32);
     
     private final static int width = 400;
     private final static int height = 400;
     private final static int halfWidth = width / 2;
     private final static int halfHeight = height / 2;

     private final static ScreenSettings defaultScreenSettings = new ScreenSettings(
          width,
          height,
          Color.GRAY,
          Color.GREEN,
          textFont,
          "CH 2 Homework by Mark Tikhonov"
     );

     public static Draw standardScreen(ScreenSettings settings){
          Draw screen = new Draw();

          //scaling the screen
          screen.setCanvasSize(settings.width, settings.height);
          screen.setXscale(0, settings.width);
          screen.setYscale(settings.height, 0);
          screen.setTitle(settings.title);
          screen.clear(settings.backgroundColor);
       
          screen.setPenColor(Color.BLACK);

          //writing my name
          screen.setFont(nameFont);
          screen.text(halfWidth, nameFont.getSize(), "Mark Tikhonov");

          //drawing delimter lines as a proof of concept
          screen.line(halfWidth, settings.height, halfWidth, 0);
          screen.line(0, halfHeight, settings.width, halfHeight);

          //setting desired writing settings
          screen.setFont(settings.font);
          screen.setPenColor(settings.penColor);
          return screen;
     }

     // writes the desired lines on a screen with (x,y) as the starting point from the left of the text,
     // as the end of lines is reached, the y value is increased by the font size
     public static Draw writeLines(Draw screen, int x, int y, String []lines){

          int yOffset = screen.getFont().getSize();
          y += yOffset;
          for (var line : lines){ // I have seen this in the quiz so it's reasonable to use it
               screen.textLeft(x, y, line);
               y += yOffset;
          }

          return screen;
     }

     // for all the methods below, I outputed the results to the console and the screen
     // As the book and assignment required different outputs
     // with this I acquired user input only through the terminal
     public static void nameAgeIncome(){
          String name = "Mark Tikhonov";
          int age = 20;
          double annualPay = 1E6;

          var screen = standardScreen(defaultScreenSettings);
          writeLines(
               screen,
               halfWidth,
               halfHeight,
               new String[]{
                    "My name is ",
                    name,
                    "My age is " + age,
                    " and I hope to",
                    "earn $" + annualPay, 
                    "per year."
               }
          ); // it is impossible to fit it otherwise;
          System.out.println("My name is " + name + ", my age is " + age + " and\nI hope to earn $" + annualPay + " per year.");
     }


     public static void personalInfo(){
          String name = "Mark Tikhonov";
          String address = "55 Barranca Pkwy, Irvine, CA 92618"; // not real address as I save my assignments in git
          String telephone = "(714) 555-1212"; // not real phone number
          String major = "Computer Science";
          Draw screen = standardScreen(defaultScreenSettings);
          writeLines(
               screen,
               halfWidth,
               halfHeight,
               new String[]{
                    name,
                    address,
                    telephone,
                    major
               }
          );
          System.out.println(name + "\n" + address + "\n" + telephone + "\n" + major);
     }

     public static void salesPredict(){
          double sales = 4.6E6;
          double percent = 0.62;

          var screen = standardScreen(defaultScreenSettings);
          writeLines(
               screen,
               halfWidth,
               halfHeight,
               new String[]{
                    "The sales prediction",
                    "for this year is",
                    "$" + sales * percent
               }
          );
          System.out.println("The sales prediction for this year is $" + sales * percent);

     }

     public static void salesTax(){
          Scanner scanner = new Scanner(System.in);
          Draw screen = standardScreen(defaultScreenSettings);
          System.out.println("Enter the amount of purchase: ");
          double purchase = scanner.nextDouble();
          final double stateTax = 0.04;
          final double countyTax = 0.02;
          final double totalTax = stateTax + countyTax;
          double total = purchase * (1 + totalTax);

          String []lines = {
               "purchase = $" + purchase,
               "state sales tax = %" +  stateTax,
               "county sales tax = %" + countyTax,
               "total sales tax = %" + totalTax,
               "total sale = $" + total
          };
          for (var line : lines) System.out.println(line);
          writeLines(screen, halfWidth, halfHeight, lines);
          scanner.close();
     }

     public static void milesPerGal(){
          Scanner scanner = new Scanner(System.in);
          var screen = standardScreen(defaultScreenSettings);
          System.out.println("Enter the number of miles driven:");
          double miles = scanner.nextDouble();
          System.out.println("Enter the gallons of gas used:");
          double gallons = scanner.nextDouble();
          double mpg = miles / gallons;
          System.out.println("The car's miles-per-gallon is " + mpg);

          writeLines(screen, halfWidth, halfHeight, new String[]{
               "The car's",
               "miles-per-gallon", 
               "is " + mpg
          });

          scanner.close();
     }

     public static void circuitBoard(){
          Scanner scanner = new Scanner(System.in);
          var screen = standardScreen(defaultScreenSettings);
          System.out.println("Enter retail price:");
          double retailPrice = scanner.nextDouble();
          double profit = retailPrice * 0.4;

          System.out.println("The profit from the circuit board is $" + profit);
          writeLines(screen, halfWidth, halfHeight, new String[]{
               "The profit from the",
               "circuit board is",
               "$" + profit
          });
          scanner.close();
     }

     public static void restaurantBill(){
          Scanner scanner = new Scanner(System.in);
          var screen = standardScreen(defaultScreenSettings);
          System.out.println("Enter the charge for the meal:");
          double mealCharge = scanner.nextDouble();
          double tax = mealCharge * 0.0675;
          double tip = (mealCharge + tax) * 0.15;
          double total = mealCharge + tax + tip;

          String []lines = {
               "Meal charge: $" + mealCharge,
               "Tax: $" + tax,
               "Tip: $" + tip,
               "Total: $" + total
          };
          for (var line : lines) System.out.println(line);

          writeLines(screen, halfWidth, halfHeight, lines);
          scanner.close();
     }
     public static void main(String []args){

          //nameAgeIncome();
          //personalInfo();     
          //salesPredict();
          //salesTax();
          //milesPerGal();
          //circuitBoard();
          //restaurantBill();
     }
}
