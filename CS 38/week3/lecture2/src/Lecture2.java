import java.awt.Color;
import java.util.Random;

public class Lecture2 {
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
         private String title;
         public ScreenSettings(int width, int height, Color backgroundColor, String title){
              this.width = width;
              this.height = height;
              this.backgroundColor = backgroundColor;
              this.title = title;
          }
     }
    
     public static Draw standardScreen(ScreenSettings settings){
          Draw screen = new Draw();
          screen.setCanvasSize(settings.width, settings.height);
          screen.setXscale(0, settings.width);
          screen.setYscale(settings.height, 0);
          screen.setTitle(settings.title);
          screen.clear(settings.backgroundColor);
          return screen;
     }

     public static void main(String []args){

          var settings = new ScreenSettings(400, 400, Color.GREEN, "mark tikhonov");
          Draw screen = standardScreen(settings);
          Random rand = new Random();

          for (int i = 1; i < 10; i ++ )
          {    
               screen.setPenColor(rand.nextInt(0, 255), rand.nextInt(0, 255), rand.nextInt(0, 255));
               screen.filledEllipse(200, 200, 200 / i, 100 / i);
          }
     } 
}
  
  