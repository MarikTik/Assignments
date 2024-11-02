import java.awt.Color;
import java.awt.Font;
import java.awt.Polygon;

public class Program {
    private static Font defaultFont = new Font("Arial", Font.PLAIN, 32);
    private static int width = 400, height = 400;
    private static Color backgroundColor = Color.BLACK;
    private static Color foregroundColor = Color.GREEN;
    private static Form form = new Form(width, height, backgroundColor, foregroundColor, defaultFont, "Program by Mark");

    public static void main(String[] args){
        var screen = form.create();
        var polygon = new Polygon2D(new Point[]{new Point(1, 100), new Point (200,200), new Point(10, 10)});
        polygon.showFilled(screen);
    }
}
