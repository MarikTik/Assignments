import java.util.Scanner;
import java.awt.Font;
/**
 * Description
 * class with all the required methods from homework 4
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
class Program{
     public static void bodyMassIndex(){
          Scanner scanner = new Scanner(System.in);
          Draw screen = new Draw();
          screen.setCanvasSize(400, 400);
          screen.clear(Draw.GRAY);
          screen.setXscale(0, 400);
          screen.setYscale(400, 0);
          screen.setPenColor(Draw.BLACK);
          screen.line(200, 0, 200, 400);
          screen.line(0, 200, 400, 200);
          screen.setPenColor(Draw.BLUE);
          screen.setTitle("body Mass Index by Mark Tikhonov");
          screen.setFont(new Font("Arial", Font.PLAIN, 24));
          
          System.out.print("Enter weight: ");
          double weight = scanner.nextDouble();
          System.out.print("Enter height: ");
          double height = scanner.nextDouble();
          double BMI = (weight * 703) / (height * height);

          String header = "Your status is: ";
          String status;
          if (BMI < 18.5)
               status = "Underweight";
          else if (BMI > 25)
               status = "Overweight";
          else 
               status = "Optimal";

          System.out.println(header + status);
          screen.textLeft(200, 100, header);     
          screen.textLeft(200, 150, status);
          scanner.close();
     }

     public static void massAndWeight(){
          Scanner scanner = new Scanner(System.in);
          Draw screen = new Draw();
          screen.setCanvasSize(400, 400);
          screen.clear(Draw.GRAY);
          screen.setXscale(0, 400);
          screen.setYscale(400, 0);
          screen.setPenColor(Draw.BLACK);
          screen.line(200, 0, 200, 400);
          screen.line(0, 200, 400, 200);
          screen.setPenColor(Draw.BLUE);
          screen.setTitle("mass and weight by Mark Tikhonov");
          screen.setFont(new Font("Arial", Font.PLAIN, 24));

          System.out.print("Enter mass: ");
          double weight =  scanner.nextDouble() * 9.8;
          String header = "The object is ";
          String message;
          if (weight > 1000)
               message = "too heavy";
          else if (weight < 10)
               message = "too light";
          else 
               message = "optimal";
          
          System.out.println(header + message);
          screen.textLeft(200, 100, header);
          screen.textLeft(200,150, message);
          scanner.close();
     }
     public static void main(String []args){
          //bodyMassIndex();
          //massAndWeight();
     }
     
}




