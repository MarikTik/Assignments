//package week7.homework6.src;
import java.awt.Font;
import java.util.Random;

/**
* Description
* class with all the required methods from homework 6
* 
* @author Mark Tikhonov
* @version 0.0.1
*/
public class Program {
    private static final int width = 400, height = 400;
    private static Random rand = new Random();

    public static void drawFlashLight(){
        var screen = new Form(
            width,
            height,
            Draw.BLACK,
            Draw.WHITE,
            new Font("Arial", Font.BOLD, 20),
            "Flash Light By Mark Tikhonov"
        ).create();
        
        //flashlight
        screen.setPenColor(62, 62, 62);
        screen.filledPolygon(new double[]{195, 205, 205, 210, 190, 195}, new double[]{290, 290, 230, 220, 220, 230});
       
        //lights
        screen.setPenColor(171, 171, 171);
        screen.filledPolygon(new double[]{208, 380, 20, 192}, new double[]{220, 0, 0, 220});
        screen.setPenColor(221, 221, 221);
        screen.filledPolygon(new double[]{206, 350, 50, 194}, new double[]{220, 0,0, 220});
        screen.setPenColor(240, 240, 240);
        screen.filledPolygon(new double[]{205, 320, 80, 195}, new double[]{220, 0, 0, 220});
        screen.setPenColor(Draw.WHITE);
        screen.filledPolygon(new double[]{204, 280, 120, 196}, new double[]{220, 0, 0, 220});
    
        //light epicenter
        screen.filledEllipse(200, 220, 10, 3);

        //grid
        screen.setPenColor(Draw.GRAY);
        for (int i = 0; i < width; i+= width/10)
            screen.line(i, 0, i, height);
        for (int i = 0; i < height; i+= height/10)
            screen.line(0, i, width, i);
        screen.setPenColor(Draw.WHITE);
        screen.text(200, 380, "Flashlight FOUR by Mark Tikhonov");
    }
    public static void diceGame(){
        var screen = new Form(
            width,
            height,
            Draw.WHITE,
            Draw.BLACK,
            new Font("Arial", Font.BOLD, 32),
            "Dice Game by Mark Tikhonov"
        ).create();

        int userScore = 0, computerScore = 0;
        for (int i = 0; i < 10; i++){
            int computerDice = rand.nextInt(6) + 1;
            int userDice = rand.nextInt(6) + 1;

            if (computerDice > userDice)
                computerScore++;
            else if (computerDice < userDice)
                userScore++;
        }
        String message;
        if (userScore > computerScore)
            message = "You won!";
        else if (userScore < computerScore)
            message = "Computer won!";
        else
            message = "It's a Draw!";
        screen.text(200, 100, "User Score: " + userScore);
        screen.text(200, 200, "Computer Score: " + computerScore);
        screen.text(200, 300, message);
        System.out.println(message);
    }
    public static void main(String [] args) {
       drawFlashLight();
       diceGame();
    }
}
 