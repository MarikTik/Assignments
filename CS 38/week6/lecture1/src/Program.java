import java.awt.Color;
import java.awt.Font;
import java.util.Random;
import java.util.Scanner;
/**
 * Description
 * class with all the required methods for the current lecture 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {
    /**
     * Description
     * encapsulates some of the setup settings for Draw object screens
     * 
     * @author Mark Tikhonov
     * @version 0.0.1
     */

    private static Random rand = new Random();
    private static int width = 600, height = 600;

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
    
    public static Draw standardScreen(ScreenSettings settings){
        Draw screen = new Draw();

        //scaling the screen
        screen.setCanvasSize(settings.width, settings.height);
        screen.setXscale(0, settings.width);
        screen.setYscale(settings.height, 0);
        screen.setTitle(settings.title);
        screen.clear(settings.backgroundColor);
        screen.setFont(settings.font);  
        screen.setPenColor(settings.penColor);
        return screen;
    }
    public static Draw writeLines(Draw screen, int x, int y, String []lines){
        int yOffset = screen.getFont().getSize();
        y += yOffset;
        for (var line : lines){ // I have seen this in the quiz so it's reasonable to use it
            screen.textLeft(x, y, line);
            y += yOffset;
        }
    
        return screen;
    }

    // accepts newlines as a way to split a single line into pieces
    public static Draw writeLine(Draw screen, int x, int y, String line){
        writeLines(screen, x, y, line.split("[\n]"));
        return screen;
    }
    public static void randomNumbers(){
        Draw screen = standardScreen(
            new ScreenSettings(
                width,
                height,
                Draw.ORANGE,
                Draw.BLACK,
                new Font("Arial", Font.ITALIC,24),
                ""
            )
        );

        writeLine(screen, 10, 100, "Random numbers by Mark Tikhonov");
        for (int x = 10; x < 400; x+=30){
            int number = rand.nextInt(10, 99);
            screen.textLeft(x, 160, "" + number);
        }
    }

    public static void drawSpookyEye(Draw screen, int x, int y, Color color){
        screen.setPenColor(color);
        screen.filledEllipse(x, y, 6, 18);
        screen.setPenColor(Color.BLACK);
        screen.filledCircle(x, y, 2);
    }
    public static void spookyEyes(int number){
        Draw screen = standardScreen(
            new ScreenSettings(
                width,
                height,
                Draw.BLACK,
                Draw.BLACK,
                new Font("Arial", Font.ITALIC,24),
                ""
            )
        );
        int hw = width / 2;
        int hh = height / 2;
        Color color;
        for (int i = 0; i < number; i++){
            int x = rand.nextInt(10, width - 10);
            int y = rand.nextInt(10, height - 10);
            if (x <= hw && y <= hh)
                color = Draw.YELLOW;
            else if (x >= hw && y <= hh)
                color = Draw.CYAN;
            else if (x <= hw && y >= hh)
                color = Draw.GREEN;
            else 
                color = Draw.PINK;

            drawSpookyEye(screen, x, y, color);
        }
    }
    
    public static void slantedLine(Draw screen, double x0, double y0, double length, double angle){
        double radians = Math.PI / 180 * angle;
        double xOffset = length * Math.cos(radians);
        double yOffset = length * Math.sin(radians);        
        double x1 = x0 + xOffset;
        double y1 = y0 - yOffset;
        screen.line(x0, y0, x1, y1);
    }
    public static void strangeRain(int number){
        Draw screen = standardScreen(
            new ScreenSettings(
                width,
                height,
                Draw.BLACK,
                Draw.BLACK,
                new Font("Arial", Font.ITALIC,24),
                ""
            )
        );
        int lineOffset = 10;
        screen.setPenColor(Draw.MAGENTA);
        for (int i = 0; i < number; i++){
            int x = rand.nextInt(lineOffset, width - lineOffset);
            int y = rand.nextInt(lineOffset, height - lineOffset);
            int lineLength = rand.nextInt(20, 50);
            slantedLine(screen, x, y, lineLength, 150);       
        }
          
    }   

    public static void multyValuedSwitch(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter any of the following letters: {A, B, C, D, E, F}");
        String input = scanner.next();
        char c = input.charAt(0);
        switch (c) {
            case 'A', 'B', 'C' -> System.out.println("Inputted either A, B or C");
            case 'D', 'E', 'F' -> System.out.println("Inputted either D, E or F");
            default -> System.out.printf("You weren't supposed to input %s", input);
        }
        scanner.close();
    }
    public static void main(String []args){
        //randomNumbers();
        //spookyEyes(1000);
        //strangeRain(1000);
        multyValuedSwitch();



    }
}
