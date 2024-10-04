import java.awt.Color;
import java.awt.Font;
import java.awt.event.MouseEvent;

/**
 * Description
 * class with all the required methods for the current lecture 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {
    private static final int width = 400, height = 400;

    private static class Form{
        public int width;
        public int height;
        public Color backgroundColor;
        public Color penColor;
        public Font font;
        public String title;

        public Form(int width, int height, Color backgroundColor, Color penColor, Font font, String title){
            this.width = width;
            this.height = height;
            this.backgroundColor = backgroundColor;
            this.penColor = penColor;
            this.font = font;
            this.title = title;
        }
        public Draw create(){
            Draw screen = new Draw();
            //scaling the screen
            screen.setCanvasSize(width, height);
            screen.setXscale(0, width);
            screen.setYscale(height, 0);
            screen.setTitle(title);
            screen.clear(backgroundColor);
            screen.setFont(font);  
            screen.setPenColor(penColor);
            return screen;
        }
    }

    /**A general interface for a function that accetps a variable x, and variable number of parameters**/
    public interface Function{
        /**
        * method template for computable functions of the form f(x, p1, p2, ..., pn)
        * @arg variable - the dependant variable of the function
        * @arg parameters - sequence of independant variables of the function.
        **/
        public double compute(double variable, double... parameters);
    }
    /**Graphing utility to sketch single variable functions on Draw canvas**/
    public static class Graph{
        public Graph(Draw form, int width, int height, boolean reverse){
            this._form = form;
            this._width = width;
            this._height = height;
            this._reverse = reverse;
        }
        public void setWidth(int width){
            this._width = width;
        }
        public void setHeight(int height){
            this._height = height;
        }
        public void setReverse(boolean reverse){
            this._reverse = reverse;
        }
        public void sketch(Function f, double... parameters){
            
            double xShift = 0.05;
            for (double x0 = 0, x1 = xShift; x1 <= _width; x0 += xShift, x1 += xShift){
                double y0 = f.compute(x0, parameters);
                double y1 = f.compute(x1, parameters);
                //System.out.printf("(%f, %f), (%f, %f)\n", x0, y0, x1, y1);
                if (_reverse)
                    y1 = _height - y1;
                _form.line(x0, y0, x1, y1);
            }
        }

        private Draw _form;
        private int _width;
        private int _height;
        private boolean _reverse;
    }
    public static double sine_wave(double x, double amplitude, double period, double xShift, double verticalShift){
        //System.out.printf("x= %f, a = %f, p = %f, hs = %f, vs = %f\n", x, amplitude, period, xShift, verticalShift);
        return amplitude * Math.sin((Math.PI * 2) / period * x + xShift) + verticalShift;
    }

    public static void drawOwl(){
        var form = new Form(
            400,
            400,
            Draw.BLACK,
            Draw.BLACK,
            new Font("Arial", Font.PLAIN, 24),
            "Owl By Mark Tikhonov"
        ).create();
        Color lightBlue = new Color(112, 128, 144);
        Color headBrown = new Color(139, 69, 19);
        Color wingBrown = new Color(160, 82, 45);
        Color bodyBrown = new Color(210, 180, 140);
        Color bellyColor = new Color(245, 222, 179);

        form.setPenColor(lightBlue);
        form.filledRectangle(200, 200, 200, 200);

        //body
        form.setPenColor(bodyBrown);
        form.filledEllipse(200, 280, 140, 90);

        //belly
        form.setPenColor(bellyColor);
        form.filledEllipse(200, 300, 100, 70);
        //wings
        form.setPenColor(wingBrown);
        form.filledEllipse(70, 270, 30, 70);
        form.filledEllipse(330, 270, 30, 70);
        form.setPenColor(headBrown);
        //head
        form.filledEllipse(200, 160, 150, 120);
        //ear 1
        form.filledPolygon(new double[]{60, 80,120}, new double[]{140, 20,60});
        //ear 2
        form.filledPolygon(new double[]{280, 320, 340}, new double[]{60, 20, 140});

        form.setPenColor(bellyColor);



 
    }   

    public static void main(String []args){
        Function f = (x, p) -> sine_wave(x, p[0], p[1], p[2], p[3]);
        var form = new Form(
            width,
            height, 
            Draw.WHITE,
            Draw.BLACK,
            new Font("Arial", Font.PLAIN, 24),
            "sine function sketch"
        ).create();
        var graph = new Graph(form, width, height, false);
        graph.sketch(f, 100,50 , 0, 100);
        form.setPenColor(Draw.PINK);
        graph.sketch(f, 100, 50, 0, 300);
    }
}
