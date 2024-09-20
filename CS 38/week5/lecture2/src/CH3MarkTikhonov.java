import java.awt.Font;
import java.util.Scanner;
import java.util.HashSet;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;


/**
 * Description 
 * examplese from classroom
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class CH3MarkTikhonov
{
     
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
        //                       012345678901
        String abc = new String("unforgetable");
        //words are {for, get, forget, table, able}
        // substring takes a subsequence from {a, b) not including b
        var words = new String[]{
            abc.substring(2, 5), 
            abc.substring(5, 8),
            abc.substring(2, 8),
            abc.substring(7),
            abc.substring(8)
        };
        for (var word : words)
            System.out.println(word);

        
    }
    public static HashSet<String> englishSubstrings(String str){
        
        File file = new File("week5/lecture2/dictionary.txt");
        HashSet<String> dictionary = new HashSet<>();
        HashSet<String> properWords = new HashSet<>();
        Scanner scanner;
        try {
            scanner = new Scanner(file);
            while (scanner.hasNext()){
                String word = scanner.next();
                
                dictionary.add(word);
            }
            for (int i = 1; i < str.length(); i++){
                for (int j = i + 1; j <= str.length(); j++){
                    String substring = str.substring(i, j);
                    if (dictionary.contains(substring))
                        properWords.add(substring);
                }
            }
        
            scanner.close();
        }
        catch (FileNotFoundException ex){
            System.out.println(ex.getMessage());
        }
        return properWords;
    }
    public static void differentSubstring(){
        //            0123456789
        String str = "automobile";
        // words {auto, mob, mobile, tom, bile}
        var words = new String[]{
            str.substring(0, 4),
            str.substring(4, 7),
            str.substring(4),
            str.substring(2, 5),
            str.substring(6)
        };

        for (var word : words)
            System.out.println(word);

    }

    public static void simpleLoop(){
            
        Draw screen = new Draw();
        screen.setCanvasSize(400, 400);
        screen.setXscale(0, 400);
        screen.setYscale(400, 0);
        screen.clear(Draw.YELLOW);
        
        Random rand = new Random();

        for (int i = 0; i < 123;i++){
            double x = rand.nextDouble(400), y = rand.nextDouble(400);
            double radius = rand.nextDouble(5, 6);
            screen.setPenColor(rand.nextInt(0, 255), rand.nextInt(0, 255), rand.nextInt(0, 255));
            screen.filledCircle(x, y, radius);
        }
    }

    public static void main(String []args){
        // for (var word : englishSubstrings("automobile")){
        //     System.out.println(word);
        // }
   
        simpleLoop();

    }
}
