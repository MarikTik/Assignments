import java.awt.Color;
import java.awt.Font;
//import java.math;

/**
 * Description
 * lecture code
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {

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

    public static <T> T[] subArray(T []array, int begin, int end){
       
        Object[] partialArray = new Object[end - begin];
        for (int i = begin; i < end; i++)
            partialArray[i - begin] = array[i];
        
        return (T[])partialArray;
    }
   
    public static void main(String []args){
        Draw draw = new Draw();
        draw.setCanvasSize(400, 400);
        draw.setXscale(0, 400);
        draw.setYscale(400, 0);

        double[] xArray = new double[400];
        double[] yArray = new double[400];
        for (int x = 0; x < 50; x++){
            xArray[x] = x * 8;
            yArray[x] = Math.sin(8 * x) * 100 + 200;
        }
        draw.polygon(xArray, yArray);
    }    
}
