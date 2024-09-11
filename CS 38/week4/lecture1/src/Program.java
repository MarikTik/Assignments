import java.util.Scanner;
import java.awt.Color;
import java.awt.Font;
import java.util.Random;

/**
 * Description
 * lecture code
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {
     void drawTarget(){

          Draw draw = new Draw();

        
          draw.setCanvasSize(400, 400);
          draw.setXscale(0, 400);
          draw.setYscale(400, 0);
          draw.clear(Draw.GRAY);
          draw.setPenColor(Color.BLACK);
          draw.line(0, 0, 400, 400);
          draw.line(0, 400, 400, 0);
          draw.setFont(new Font("Arial", Font.PLAIN, 24));

          draw.setPenColor(Draw.RED);
          draw.filledCircle(200, 60, 60);
          draw.setPenColor(Draw.WHITE);
          draw.filledCircle(200, 60, 40);
          draw.setPenColor(Draw.RED);
          draw.filledCircle(200, 60, 20);
          draw.text(200, 140, "TARGET");
          

          draw.filledCircle(70, 165, 60);
          draw.setPenColor(Draw.WHITE);
          draw.filledCircle(70, 165, 40);
          draw.setPenColor(Draw.RED);
          draw.filledCircle(70, 165, 20);
          draw.text(70, 250, "TARGET");

          draw.filledCircle(200, 300, 60);
          draw.setPenColor(Draw.WHITE);
          draw.filledCircle(200, 300, 40);
          draw.setPenColor(Draw.RED);
          draw.filledCircle(200, 300, 20);
          draw.text(200, 380, "TARGET");

          draw.filledCircle(330, 165, 60);
          draw.setPenColor(Draw.WHITE);
          draw.filledCircle(330, 165, 40);
          draw.setPenColor(Draw.RED);
          draw.filledCircle(330, 165, 20);
          draw.text(330, 250, "TARGET");

     }

     public static void drawPanda(){
          Draw screen = new Draw();
          screen.setCanvasSize(400, 400);
          screen.setXscale(0, 400);
          screen.setYscale(400, 0);
          screen.clear(Draw.GRAY);

          //body
          screen.filledEllipse(200, 400, 160, 200);

          // ears
          screen.filledCircle(100, 100, 50);
          screen.filledCircle(300, 100, 50);
          // head
          screen.setPenColor(Draw.WHITE);
          screen.filledCircle(200, 200, 125);

          // nose
          screen.setPenColor(Draw.BLACK);
          screen.filledEllipse(200, 200, 25, 15);
          
          // eye holes
          screen.filledEllipse(155, 170, 25, 35);
          screen.filledEllipse(245, 170, 25, 35);

          // eyes
          screen.setPenColor(Draw.WHITE);
          screen.filledCircle(160, 160, 15);
          screen.filledCircle(240, 160, 15);
          screen.setPenColor(Draw.BLACK);
          screen.filledCircle(160, 160, 5);
          screen.filledCircle(240, 160, 5);
          
          // mouth
          screen.setPenColor(Draw.RED);
          screen.filledEllipse(200, 260, 30, 20);
          screen.setPenColor(Draw.WHITE);
          screen.filledRectangle(200, 240, 30, 15);

          screen.setPenColor(Draw.GREEN);
          double[] xS = new double[]{30, 15, 185, 215};
          double[] yS = new double[]{380, 370, 250, 270};
          screen.filledPolygon(xS, yS);

     }
     public static void main(String []args){
          drawPanda();
     }    
}
