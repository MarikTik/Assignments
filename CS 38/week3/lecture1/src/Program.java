/**
 * Description
 * lecture work
 * @author Mark TIkhonov
 * @version 0.0.1
 */

public class Program {
    
    public static int puzzle3(){
        // notice that "Squere" really stands for "Rectangle" in this problem
        int whiteSquereArea = 56;
        int whiteSquereHeight = 7;
        int whiteSquereWidth = whiteSquereArea / whiteSquereHeight;
        int whiteSquereKnownSideWidth = 4;
        int whiteSquereUnknownSideWidth = whiteSquereWidth - whiteSquereKnownSideWidth;
        int greySquereKnownSideWidth = 5;
        int greySquereSideWidth = greySquereKnownSideWidth + whiteSquereUnknownSideWidth;
        int greySquereSideHeight = 6;
        int greySquereArea = greySquereSideHeight * greySquereSideWidth; // this is the answer,
        return greySquereArea;
        // the variable names should be pretty self explanatory.
    }

    public static int puzzle4(){
        int figureLeftSideHeight = 9;
        int figureBottomRightSideHeight = 5;
        int figureTopRightSideHeight = figureLeftSideHeight - figureBottomRightSideHeight;
        int topRectangleArea = 24;
        int topRectangleWidth = topRectangleArea/ figureTopRightSideHeight;
        int greyRectangleArea = topRectangleWidth * figureBottomRightSideHeight; // final answer
        return greyRectangleArea;
    }

    private static String name = "Mark Tikhonov";
    private static int verticalOffset = 12;
    private static Draw screen = new Draw();
    
    public static void displayPuzzleSolution(String puzzleID, int result){

        int width = 400; int height = 400;
        if (verticalOffset == 12){ // this happens only once
            screen.setCanvasSize(width, height);
            screen.setXscale(0, 400);
            screen.setYscale(0, 400);
            screen.setTitle("puzzle solved by " + name);
            screen.clear(Draw.PINK);
        }

        screen.setPenColor(Draw.BLACK);
        screen.text(100, 400 - verticalOffset, puzzleID + " result = " + result);
        verticalOffset += 15;
    }


    public static void main(String []args){

        // displayPuzzleSolution("puzzle 3", puzzle3());
        // displayPuzzleSolution("puzzle 4", puzzle4());
    }
}


/**
* Description
* This program calculates the sale price of
* an item that is regularly priced at $59,
* with a 20 percent discount subtracted.
* ref: pg __________
* @author Mark Tikhonov
* @version 0.0.1
*/
public class DiscountYName
{
    public static void discount( )
    {
        // Variables to hold the regular price, the
        // amount of a discount, and the sale price.
        double regularPrice = 59.0;
        double discount;
        double salePrice;
        // Calculate the amount of a 20% discount.
        discount = 0.123;
        // Calculate the sale price by subtracting
        // the discount from the regular price.
        salePrice = 123;
        // Display the results.
        System.out.println("Regular price: $" + regularPrice);
        System.out.println("Discount amount $" + discount);
        System.out.println("Sale price: $" + salePrice);

        //Expected output =========
    //Regular price: $59.0
    //Discount amount $11.8
    //Sale price: $47.2
    }
    public static void main(String []args){
        discount();
    }
}