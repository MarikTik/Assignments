import java.util.Scanner;
import java.awt.Font;
import java.awt.Color;

class Program{
    private static Font defaultFont = new Font("Arial", Font.ITALIC, 32);
    private static int width = 400, height = 400;
    private static Color backgroundColor = Color.BLACK;
    private static Color textColor = new Color(58, 65, 74);
    private static Scanner scanner = new Scanner(System.in);

    private static Form defaultForm = new Form(
        width,
        height,
        backgroundColor,
        textColor,
        defaultFont,
        "Program by Mark"
    );
    public static void main(String []args){
        var screen = defaultForm.create();
        Asteroid asteroid = new Asteroid(screen, 100, 100);
        asteroid.show(200, 200);
        //screen.enableDoubleBuffering();
        
     
        //screen.show();
    }

    // double amplitude = 150;
    // double x = 200;
    // double frequency = 0.01;
    // double y0 = amplitude;
    // double stretch = 0.25;
    // for (double t = 0; ;t+=0.05){
    //     double y = amplitude * Math.cos(frequency * t -Math.PI);
    //     screen.setPenColor(backgroundColor);
    //     screen.filledRectangle(x, y0 + 200, 50 + stretch, 50 + stretch);
    //     screen.setPenColor(Color.GREEN);
    //     screen.filledRectangle(x, y + 200, 50, 50);
    //     y0 = y;
    //     screen.show();
    // }
}