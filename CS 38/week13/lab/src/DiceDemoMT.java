import java.util.Random;

public class DiceDemoMT {

    public void play(){
        int []lose_values = new int[]{3, 4, 5, 6, 7, 8};
        int []win_values = new int[]{10, 11};

        ThreeDiceMT dice = new ThreeDiceMT();
        int []scores = new int[20];
        String template = "%s:\t%s";
        int goal = -1;

        for (int i = 0; i < scores.length; i++){
            dice.roll();
            scores[i] = dice.diceSum();

            if (contains(win_values, scores[i]) || scores[i] == goal){
                System.out.print("You win:\t");
                printArray(scores);
                return;
            }
            if (contains(lose_values, scores[i])){
                System.out.print("You lose:\t");
                printArray(scores);
                return;
            }
            goal = scores[i];
        }

        System.out.print("Inconclusible:\t");
        printArray(scores);
    }

    public static void demo(int runs){
        var diceDemo = new DiceDemoMT();
        System.out.println("Dice Game by Mark Tikhonov");
        for (int i = 0; i < runs; i++)
            diceDemo.play();
    }

    private void printArray(int array[]){
        for (int i = 0; i < array.length; i++){
            System.out.print(array[i] + " ");
            if ((i + 1) % 5 == 0)
                System.out.print(" - ");
        }
        System.out.println();
    }
    private static boolean contains(int []arr, int value){
        for (int i : arr)
            if (value == i)
                return true;
        
        return false;
    }

}
 