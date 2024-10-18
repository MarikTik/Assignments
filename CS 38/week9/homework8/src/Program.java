import java.awt.Color;
import java.awt.Font;
import java.util.Scanner;

public class Program {
    private static Font defaultFont = new Font("Arial", Font.PLAIN, 12);
    private static int width = 400, height = 400;
    private static Color backgroundColor = new Color(176, 196, 222);
    private static Color textColor = new Color(58, 65, 74);

    private static Form defaultForm = new Form(
        width,
        height,
        backgroundColor,
        textColor,
        defaultFont,
        "Program by Mark"
    );
    public static void cookieAdvanced(){ // this is the function that allows to bite by clicks
        var screen = defaultForm.create();
        var cookie = new Cookie(screen,width * 0.75, height * 0.25, width * 0.25);
        var bitableCookie = cookie.show(50);

        screen.addListener(new DrawListener() {
            public void mouseClicked(double x, double y){
                bitableCookie.bite(x, y, 30, backgroundColor);
            }
        });
    }

    public static void cookieSimple(){
        var screen = defaultForm.create();
        var cookie = new Cookie(screen,width * 0.75, height * 0.25, width * 0.25);
        var bitableCookie = cookie.show(10);
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("usage <bite/b, quit/q> optional <x, y> where");
        
    }
    public static void main(String []args){
        cookieAdvanced();
    }       
}
