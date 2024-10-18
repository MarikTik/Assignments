import java.awt.Color;
import java.awt.Font;
import java.util.Scanner;

public class Program {
    private static Font defaultFont = new Font("Arial", Font.ITALIC, 32);
    private static int width = 400, height = 400;
    private static Color backgroundColor = new Color(176, 196, 222);
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
    // question 1
    public static void showChar(String str, int pos){
        System.out.println(str.charAt(pos));
    }

    //question 2
    public static double getWidht(){
        return Double.parseDouble(scanner.next());
    }
    public static double getHeight(){
        return Double.parseDouble(scanner.next());
    }
    public static double getArea(double width, double height){
        return width * height;
    }
    public static void displayData(double width, double height, double area){
        System.out.printf("Width: %f\nHeight: %f\nArea: %f\n", width, height, area);
    }
    public static void areaRectangle(){
        double width = getWidht();
        double height = getHeight();
        double area = getArea(width, height);
        displayData(width, height, area);
    }   

    // question 5
    public static double fallingDistance(double t){
        double g = 9.81;
        return 0.5 * g * Math.pow(t, 2);
    }
    public static void demostateFallingDistance(){
        for (int i = 1; i <= 10; i++)
            System.out.printf("Time: %s, Distance: %s\n", i, fallingDistance(i));
    }

    // challenge
    public static void simpleCookie(){
        var screen = defaultForm.create();
        screen.text(width / 4, height / 2, "Mark Tikhonov 10/17", 90);
        var cookie = new Cookie(screen,width * 0.75, height * 0.25, width * 0.25);
        var bitableCookie = cookie.show(10);

        Scanner scanner = new Scanner(System.in);
        System.out.println("usage <bite (anything but 'q'), quit ('q')>");

        for (String input = scanner.nextLine(); !input.equals("q"); input = scanner.nextLine())  
            bitableCookie.bite(screen.mouseX(), screen.mouseY(), 30, backgroundColor);

        scanner.close();
    }

    public static void clickableCookie(){ // this is the function that allows to bite by clicks
        var screen = defaultForm.create();
        var cookie = new Cookie(screen,width * 0.75, height * 0.25, width * 0.25);
        var bitableCookie = cookie.show(50);

        screen.addListener(new DrawListener() {
            public void mouseClicked(double x, double y){
                bitableCookie.bite(x, y, 30, backgroundColor);
            }
        });
    }
   
    public static void main(String []args){
        //showChar("01234", 4);
        //areaRectangle();
        // demostateFallingDistance(); 
        simpleCookie();
        scanner.close();
    }       
}
