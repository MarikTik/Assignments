import java.awt.Color;

class Main
{
    public static void main(String []args)
    {
        Draw draw = new Draw();
        draw.clear(Color.BLUE);
        draw.setPenColor(Draw.RED);
        for (double i = 0; i <= 5.0; i += 0.1){
            draw.filledCircle(2, 2, i);
            draw.pause(100);
        }
        
        draw.show();
    }
};

// java -cp ../../lib/Draw.jar:. Main
// javac -Xlint:deprecation -cp ../../lib/Draw.jar:. main.java