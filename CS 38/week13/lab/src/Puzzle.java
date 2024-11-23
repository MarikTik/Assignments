import java.util.Random;

public class Puzzle {
    Puzzle(){
        table.fill(0);
    }
    public void randomFill(){
        for (int i = 0 ; i < 2; i ++)
            for (int j = 0; j < 2; j++)
                table.set(i, j, randTwoDigit());
        
        table.set(0, 2, randTwoDigit());                
        int targetSum = rowSum(table, 0);     
        System.out.println(targetSum);   
        // table.set(1, 2, randTwoDigit());
        // table.set(2, 0, randTwoDigit());
        // table.set(2, 1, randTwoDigit());
        // table.set(2, 2, randTwoDigit());
        System.out.println("found 0");
        while(rowSum(table, 1) != targetSum) table.set(1, 2, randTwoDigit());
        System.out.println("found 1");
        while(colSum(table, 0) != targetSum) table.set(2, 0, randTwoDigit());
        System.out.println("found 2");
        while(colSum(table, 1) != targetSum) table.set(2, 1, randTwoDigit());
        System.out.println("found 3");
        while(colSum(table, 2) != targetSum && rowSum(table, 2) != targetSum) table.set(2, 2, randTwoDigit());  
        System.out.println("found 4");
        // _ _ _
        // _ _ -
        // - - *
        
    }

 

    private static int randTwoDigit(){
        int num =  rand.nextInt(10, 100);
        return num;
    }

    private static int rowSum(Matrix2D matrix, int row){
        int sum = 0;
        for (int j = 0; j < matrix.height(); j++) sum += (int)matrix.get(row, j);
        return sum;
    }

    private static int colSum(Matrix2D matrix, int col){
        int sum = 0;
        for (int i = 0; i < matrix.width(); i++) sum += (int)matrix.get(i, col);
        return sum;
    }
    
    public void display(Draw screen, int width, int height){
        double xOffset = width / 3.0;
        double yOffset = height / 3.0;

        for (double i = xOffset; i < width; i += xOffset)
            screen.line(i, 0, i, height);

        for (double i = yOffset; i < height; i += yOffset)
            screen.line(0, i, width, i);
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                screen.text((i + 0.5) * xOffset, (j + 0.5) * yOffset , "" + table.get(j,i));
    }
    

    public static void demo(){
        var screen = Form.defaultForm();
        var puzzle = new Puzzle();
        puzzle.randomFill();
        puzzle.display(screen, 400, 400);
    }
    private Matrix2D<Integer> table = new Matrix2D<>(3, 3); 
    private static Random rand = new Random();
}
