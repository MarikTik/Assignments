public class Program {
    public static void main(String []args){
        //Puzzle.demo();
        Matrix2D<Integer> matrix = new Matrix2D<>(new Integer[][]{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 10}
        });
         
        for (int i = 0; i < 3; i ++)
            for (int j = 0; j < 3; j++)
                System.out.println(matrix.get(i, j));
        
    }
}
