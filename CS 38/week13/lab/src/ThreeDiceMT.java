import java.util.Random;

public class ThreeDiceMT {
    public ThreeDiceMT(){
        for (int i = 0; i < dice.length; i++)
            dice[i] = rand.nextInt(1, 7);
    }
    public ThreeDiceMT(int k, int m, int n){
        setDice(1, k);
        setDice(2, m);
        setDice(3, n);
    }
    public int getDice(int n){
        if (1 <= n && n <= 3)
            return dice[n - 1];
        if (n == 0)
            return sum(dice);
        return 0;
    }

    public void setDice(int n, int newValue){
        if (1 <= n && n <= 3 && 1 <= newValue && newValue <= 6)
            dice[n - 1] = newValue;
    }

    public void roll(){
        for (int i = 0; i < dice.length; i++)
            dice[i] = rand.nextInt(1, 7);
    }
    public String toString(){
        String s = "";
        for (int i : dice)
            s += i;
        return s;
    }

    public void printMe(){
        System.out.println(toString());
    }

    public static void demo(){
        ThreeDiceMT dice = new ThreeDiceMT();
        int []score = new int[20];
        dice.play(score);
    }

    private void printArray(int array[]){
        for (int i = 0; i < array.length; i++){
            System.out.print(array[i]);
            if ((i + 1) % 5 == 0)
                System.out.print(" - ");
        }
        System.out.println();
    }
    private int sum(int []arr){
        int s = 0;
        for (int i : arr) s+=i;
        return s;
    }

    private Random rand = new Random();
    private int[] dice = new int[3];
}



// Write a ThreeDiceYourInitials class with instance variables face, a three element array to hold values you can roll with the set of dice.
// Default constructor places random values 1..6 on each face
// Constructor with parameters n, m for the initial face values. Validate the parameters to allow only 1..6.
// Accessors getDice( int n ) whose value is
//     n=1 returns the first dice,
//     n=2 returns the second dice,
//     n=3 returns the third dice
//     n=0 returns the total of all dice
// Mutators setDice( int n, int newValue ) sets dice n to the newValue. Error Check: if n is not 1,2, or 3, do nothing, Error Check: if newValue is not 1 to 6, do nothing.  
// Mutator roll( ) which randomize the numbers on each of the three dice to 1..6
// toString( ) method to return a string like "341" meaning first dice  is 3, second is 4, third is 1. 
// printMe( ) method for DEBUG. This should simply print the value in toString( ).
// Write a demo DiceDemo1YOURNAME.
// Instantiate and initialize the three dice
// Instantiate score, a 20 element array of integers and initialize it to all 0.
//     Use a 1Dim array
// Write a play( ) method for a new game, it should reset the game and then continuously roll the dice until you win or lose or the array is full.
// Each roll is entered in the array until you win, lose, or the array is full.
// Write a printArray( ) method to print the score array on ONE line. Make it easy to read by adding a " - " after every 5 scores.
