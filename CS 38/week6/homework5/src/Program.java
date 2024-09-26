import java.util.Random;
import java.awt.Color;
import java.awt.Font;

/**
* Description
* class with all the required methods from homework 5
* 
* @author Mark Tikhonov
* @version 0.0.1
*/
public class Program {

    
     private static int width = 400, height = 400, hw = 200, hh = 200;
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

     public static Draw standardScreen(ScreenSettings settings){
         Draw screen = new Draw();

         //scaling the screen
         screen.setCanvasSize(settings.width, settings.height);
         screen.setXscale(0, settings.width);
         screen.setYscale(settings.height, 0);
         screen.setTitle(settings.title);
         screen.clear(settings.backgroundColor);
         screen.setFont(settings.font);  
         screen.setPenColor(settings.penColor);
         return screen;
     }
     public static void drawBunny(){
          Draw screen = standardScreen(
               new ScreenSettings(
                    width,
                    height,
                    Draw.GREEN,
                    Draw.PINK,
                    new Font("Times New Roman", Font.PLAIN, 32),
                    "Bunny by Mark Tikhonov"
               )
          );
          // ears
          screen.filledEllipse(75, 260, 18, 45);
          screen.filledEllipse(125, 260, 18, 45);
          screen.setPenColor(Draw.YELLOW);
          screen.filledEllipse(75, 260, 10, 37);
          screen.filledEllipse(125, 260, 10, 37);

          // head
          screen.setPenColor(Draw.WHITE);
          screen.filledCircle(70, 350, 40);
          screen.filledCircle(130, 350, 40);
          screen.filledEllipse(100, 310, 50, 35);

          // eyes
          screen.setPenColor(Draw.PINK);
          screen.filledEllipse(125, 335, 15, 25);
          screen.setPenColor(Draw.BLACK);
          screen.filledEllipse(125, 338, 7, 12);
          screen.filledEllipse(75,  338, 7, 12);
          screen.setPenColor(Draw.WHITE);
          screen.filledEllipse(125, 336, 2, 4);
          screen.filledEllipse(75,  336, 2, 4);

          // nose
          screen.setPenColor(Draw.BLACK);
          screen.filledRectangle(100, 365, 10, 5);

          // draw lines         
          screen.setPenColor(Draw.GRAY);
          for (int x = 0; x < width; x += 40)
               screen.line(x, 0, x, height);
          for (int y = 0; y < height; y += 40)
               screen.line(0, y, width, y);

          // write my name
          screen.setPenColor(Draw.RED);
          screen.text(200, 200, "Bunny by Mark Tikhonov", 90);
          
          
     }
     public static void drawBuilding(){
          Draw screen = standardScreen(
               new ScreenSettings(
                    width,
                    height,
                    Draw.PINK,
                    Draw.WHITE,
                    new Font("Arial", Font.BOLD, 24),
                    "Building by Mark Tikhonov"
               )
          );
          // draw sun
          screen.filledCircle(hw * (8/5.0), hh, hw * (1/4.0));
          screen.setPenColor(Draw.MAGENTA);

          // draw building
          screen.filledRectangle(hw, height, hw * (9/20.0), height * (1.5/10.0));
          screen.filledRectangle(hw, height - height * (1.5/10.0), hw * (2/5.0), hh / 5.0);
          screen.filledRectangle(hw, hh + hh / 20.0 , hw * (5 / 20.0), hh * (4.5 / 10.0));
          screen.filledRectangle(hw, hh * (11 / 20.0), hw * (3 / 20.0), hh * (1 / 20.0));
          screen.filledRectangle(hw, hh * (9 / 20.0), hw * (1 / 20.0), hh * (1 / 20.0));

          // draw lines
          screen.setPenColor(Draw.GRAY);
          for (int x = 0; x < width; x += 40)
               screen.line(x, 0, x, height);
          for (int y = 0; y < height; y += 40)
               screen.line(0, y, width, y);
          
          // write my name
          screen.setPenColor(Draw.BLUE);
          screen.text(hw, hh/4, "Building by Mark Tikhonov");
     }
     public static void main(String []args){
          //drawBuilding();
          drawBunny();
     }
}    
