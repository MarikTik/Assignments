import java.util.Scanner;
import java.util.Random;
//import Plot;
/**
 * Descritpion: Lecture code
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {

    public static interface function{
        double func(double ...args);
    } 
    public static class Plotter{
        public Plotter(Draw screen, int canvasWidth, int canvasHeight){
            this.screen = screen;
            this.canvasWidth = canvasWidth;
            this.canvasHeight = canvasHeight;
        }
        public void setBounds(int newWidth, int newHeight){
            canvasWidth = newWidth;
            canvasHeight = newHeight;
        }
        public void plot(function f, double...args){
            
        } 

        private Draw screen;
        private int canvasWidth, canvasHeight;
    }
    public static double f(double x, double y0, double x0,  double extension, double period){
        return y0 + extension * Math.sin((Math.PI * 2) / period * x + x0);
    }
    public static void main(String []args){
        //Plot plot = new Plot();
        Draw draw = new Draw();
        draw.setCanvasSize(400, 400);
        draw.setXscale(0, 400);
        draw.setYscale(400, 0);
        draw.clear(Draw.WHITE);
        draw.setPenColor(Draw.BLACK);
        
        
        double verticalShift = 200;
        double extension = 50;
        double period = 20; 
        double horizontalShift = 0;
        for(double x0 = 0, x1 = 1; x0 <= 400 && x1 <= 400; x0+=0.01, x1+=0.01){
            double y0 = f(x0, verticalShift, horizontalShift, extension, period);
            double y1 = f(x1, verticalShift, horizontalShift, extension, period);
            draw.line(x0, y0, x1, y1);    
        }

    }
}
