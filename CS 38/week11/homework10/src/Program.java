import java.awt.Font;
import java.awt.Color;
import java.util.Random;;
public class Program {
    private static Font defaultFont = new Font("Arial", Font.PLAIN, 32);
    private static int width = 400, height = 400;
    private static Color backgroundColor = Color.GRAY;
    private static Color foregroundColor = Color.GREEN;
    private static Form form = new Form(width, height, backgroundColor, foregroundColor, defaultFont, "Program by Mark");
    private static Random rand = new Random();

    private static Color randomColor(){
        return new Color(rand.nextInt(256), rand.nextInt(256), rand.nextInt(256));
    }
    private static class ColorPredicate implements IColorPredicate {
        @Override
        public Color colorAt(Point p) {
            double x = p.getX();
            double y = p.getY();
            if (((int)(x / 100.0 + y / 100.0 )) % 2 == 0){
                return Color.RED;
            }
            return Color.BLACK;
        }
    }

    private static class TextPredicate implements ITextPredicate {
        @Override
        public Font fontAt(Point p) {
            return new Font("Arial", Font.PLAIN, 32);
        }
        @Override
        public Color textColorAt(Point p) { 
           return randomColor();
        }
        @Override
        public String textAt(Point p) {
            return "M.T.";
        }
    }

    public static void main(String[] args){
        var screen = form.create();
        screen.enableDoubleBuffering(); 
        var polygon = new Polygon2D(new Point[]{
            new Point(50, 0), new Point (100, 50), new Point(50, 100), new Point(0, 50)
        }); 
   
    
        var board = new Board(polygon, 4);
        board.setColorPredicate(new ColorPredicate());
        board.setTextPredicate(new TextPredicate());
        board.show(screen);
        screen.show();
    }
}
