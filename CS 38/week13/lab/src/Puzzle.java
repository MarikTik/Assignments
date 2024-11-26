import java.util.Random;

public class Puzzle {
    public Puzzle(){
        table.fill(0);
    }
    public FillInfo randomFill(){
        for (int i = 0 ; i < 2; i ++)
            for (int j = 0; j < 2; j++)
                table.set(i, j, randTwoDigit());
        
        table.set(0, 2, randTwoDigit());                
        int targetSum = rowSum(table, 0);     
        
        long iterations = 0;
        while(rowSum(table, 1) != targetSum) {
            iterations++;
            table.set(1, 2, randTwoDigit());
        }
            
  
        while(colSum(table, 0) != targetSum) {
            iterations++;
            table.set(2, 0, randTwoDigit());
        }

        while(colSum(table, 1) != targetSum) {
            iterations++;
            table.set(2,1 , randTwoDigit());
        }
    
        while(colSum(table, 2) != targetSum && rowSum(table, 2) != targetSum){
            iterations++;
            table.set(2, 2, randTwoDigit());
        }
        
        // _ _ _
        // _ _ -
        // - - *
        
        return new FillInfo(table, iterations, targetSum);
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
        System.out.print(puzzle.randomFill());
        puzzle.display(screen, 400, 400);
    }
    private Matrix2D<Integer> table = new Matrix2D<>(3, 3); 
    private static Random rand = new Random();

    private static class FillInfo{
        public FillInfo(Matrix2D<Integer> table, long iterations, int targetSum){
            this.iterations = iterations;
            this.targetSum = targetSum;
            this.table = table;
        }
        public String toString(){
            return String.format(
                "try #%d: Mark Tikhonov FOUND A SOLUTION=====\n%s\n\nRow sum: %d\nColSum: %d\n",
                iterations,
                table,
                targetSum,
                targetSum
            );
        }
        private Matrix2D<Integer> table;
        private long iterations;
        private int targetSum;
    }
}
