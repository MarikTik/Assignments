import java.awt.Font;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.util.Random;
/**
 * Description
 * class with all the required methods for the current lecture 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {
    private static Font defaultFont = new Font("Arial", Font.PLAIN, 12);
    private static int width = 400, height = 400;
    private static Form defaultForm = new Form(
        width,
        height,
        Draw.BLACK,
        Draw.WHITE,
        defaultFont,
        "Program by Mark"
    );

    private static Random rand = new Random();
    public static void followingLine(){
        var screen = defaultForm.create();
        double center_x = width / 2;
        double center_y = height / 2;

        while(true){
            double x = screen.mouseX();
            double y = screen.mouseY();

            screen.line(center_x, center_y, x, y);
        }
    }

    public static void mouseClickEvent(){
        var screen = defaultForm.create();

     
        screen.addListener(new DrawListener() {
            public void mouseClicked(double x, double y){
                screen.point(x, y);
            }
        } );
    }

    public static void linedClick(){
        var screen = defaultForm.create();

        screen.addListener(new DrawListener() {
            private double x0 = -1, y0 = -1;
            public void mouseClicked(double x, double y){
                if (x0 == -1 && y0 == -1){
                    screen.point(x, y);
                }
                else{
                    screen.line(x0, y0, x, y);
                }
                x0 = x;
                y0 = y;
            }
            public void mouseDragged(double x, double y){
                System.out.println("move");;
            }
        });
        screen.addListener(new DrawListener() {
          
        });
    }

    public Color randomColor(){
        return new Color(rand.nextInt(0, 255), rand.nextInt(0, 255), rand.nextInt(0, 255));
    }
    public static void randomizePolygons(){
        var screen = defaultForm.create();
      
        double boxX = 30;
        double boxY = 30;
        double maxVerticies = 10;
        
        while (true)
            // to be continued
        }
    public static void main(String[] args){
        linedClick();
    }
}
 