import java.util.function.BiFunction;
import java.awt.Font;
import java.util.Random;
/**
 * Description
 * class with all the required methods for the current lecture 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */

public class Program {

    private static Random rand = new Random();

    public interface Function{
        public double compute(double variable, double... parameters);
    }
    public static class Graph{
        public Graph(Draw form, int width, int height, boolean reverse){
            this._form = form;
            this._width = width;
            this._height = height;
            this._reverse = reverse;
        }
        public void setConstraints(){

        }
        public void sketch(Function f, double... parameters){
            
            double horizontalShift = 0.05;
            for (double x0 = 0, x1 = horizontalShift; x1 <= _width; x0 += horizontalShift, x1 += horizontalShift){
                double y0 = f.compute(x1, parameters);
                double y1 = f.compute(y0, parameters);
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
    public static void drawCzechFlag(){
        Draw form = new Draw();
        form.setCanvasSize(400, 400);
        form.setXscale(0, 400);
        form.setYscale(400, 0);
        // right side ends at around x = 225

        form.clear(Draw.GRAY);
        form.setPenColor(Draw.BLUE);
        form.filledPolygon(new double[]{0, 0, 100}, new double[]{200, 350, 275});
        form.setPenColor(Draw.WHITE);
        form.filledPolygon(new double[]{0, 100, 225, 225},new double[]{200, 275, 275, 200});
        form.setPenColor(Draw.RED);
        form.filledPolygon(new double[]{0, 100, 225, 225}, new double[]{350, 275, 275, 350});

        form.setPenColor(Draw.ORANGE);
        form.setFont(new Font("Arial", Font.BOLD, 24));
        form.text(300, 200, "Mark Tikhonov", 90);
    }
    public static void main(String []args){
        Draw form = new Draw();
        form.setCanvasSize(400, 400);
        form.setXscale(0, 400);
        form.setYscale(0, 400);
        Function f = (x, parameters) -> parameters[0] * Math.pow(x, 2);

        Graph graph = new Graph(form, 400, 400, true);
        graph.sketch(f, new double[]{1/10.0});
    }

 
}