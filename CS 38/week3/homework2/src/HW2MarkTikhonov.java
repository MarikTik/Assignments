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
          private int width;
          private int height;
          private Color backgroundColor;
          private Font font;
          private String title;
     
          public ScreenSettings(int width, int height, Color backgroundColor, Font font, String title){
               this.width = width;
               this.height = height;
               this.backgroundColor = backgroundColor;
               this.font = font;
               this.title = title;
          }
     }
     
     public static Draw standardScreen(ScreenSettings settings){
          Draw screen = new Draw();
          screen.setCanvasSize(settings.width, settings.height);
          screen.setXscale(0, settings.width);
          screen.setYscale(settings.height, 0);
          screen.setTitle(settings.title);
          screen.setFont(settings.font);
          screen.clear(settings.backgroundColor);
          return screen;
     }
     public static void main(String []args){

           
          final ScreenSettings defaultSettings = new ScreenSettings(
               400,
               400,
               Color.GRAY,
               new Font("Arial", Font.PLAIN, 32),
               "CH 2 #1 Name, Age and Annual Income by Mark Tikhonov"
          );
          Draw draw = standardScreen(defaultSettings);

     }
}
