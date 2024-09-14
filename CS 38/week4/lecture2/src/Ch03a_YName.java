import java.awt.Font;
import java.util.Scanner;
import java.util.Random;

/**
 * Description 
 * examplese from classroom
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Ch03a_YName
{
    public static void main(String[] args)
    {
        ex03();
    }

    // I suppose that it tries to print 
    // ** Mom's age: 123
    // ** Dad's age: 123
    // but it doesn't do so, it only declares the variables
    // than it should have asked if dadAge < momAga
    // but it does so badly, so I will just fix the method to work properly
    public static void ifMomDad()
    {
        Scanner keyboard = new Scanner(System.in);
        int momAge, dadAge;
        System.out.print("Mom's age: ");
        momAge = keyboard.nextInt();
        System.out.print("Dad's age: ");
        dadAge = keyboard.nextInt();

        if( dadAge < momAge )
        {
            System.out.println("Mom is older");
        }
        else if(dadAge > momAge)
        {
            System.out.println("Dad is older");
        }
        else {
            System.out.println("They are the same age");
        }
        //What if they are same age?
        // for that the methods should be linked by a proper else cases
        
    }

    
    public static void ex03()
    {
        Scanner keyboard = new Scanner(System.in); 
        Random rand = new Random();

        System.out.print("Enter number of males, ex 24: ");
        int numMale = keyboard.nextInt(); // gets amount of males from the user

        int numFemale = rand.nextInt(50); //let computer pick it
        System.out.println("Number of females: "+numFemale);

        if(numMale > numFemale) // if there are more males than females
        {
            System.out.println("More males");
        }
        else
            System.out.println("More females"); // else if there are more females

        Draw win = new Draw();
        win.setCanvasSize(400, 400);
        win.setXscale(0, 400);
        win.setYscale(400, 0);
        win.clear(Draw.LIGHT_GRAY);
        Font fnt = new Font("Arial", Font.BOLD, 32);
        win.setFont( fnt );
        if(numMale > numFemale)
        {   
            win.text(200, 200, "there are more guys");
            //123 graphics output
        }
        else
        {
            win.text(200, 200, "there are more females");
            //123 graphics output
        }
    }  

    //ref pg220 count-control loop, four examples ====
    //Explain:
    //
    public static void if05()
    {
        //Use this to repeat instructions
        for(int count=1; count<=10; count=count+1)
        {
            //123 print your name
        }
    }

    //Explain:
    //
    public static void if06()
    {
        //Use this to repeat instructions
        for(int count=1; count<=10; count=count+1)
        {
            //123 print count all on ONE LINE
        }
    }

    //Explain:
    //
    public static void if07()
    {
        Draw yi = new Draw( );
        //Use this to repeat instructions
        for(int count=1; count<=10; count=count+1)
        {
            System.out.print(count + " ");
            yi.pause(1000);
        }
    }

    //Explain:
    //
    public static void if12( )
    {
        //ref if-else if-else
        Draw yi=new Draw( );
        yi.clear(Draw.WHITE);
        yi.setXscale(0,400);
        yi.setYscale(400,0);
        yi.setTitle("Top half is ___, else ___ by YName");

        Scanner keyboard = new Scanner(System.in);
        int x, y;
        for(int count=5; count>0; count=count-1)
        { 
            String msg = count + ") enter x and y, ex 50 140: "; 
            System.out.print( msg );
            x = keyboard.nextInt( );
            y = keyboard.nextInt( );

            //Draw cyan circle on left, red rectangle on right
            if( 123<123 )
            {
                //123 draw a solid cyan circle                
            }
            else
            {
                //123 draw solid red rectangle                
            }
        }
    }

   
   
    public static void nervousEyes( )
    {
    }

}
