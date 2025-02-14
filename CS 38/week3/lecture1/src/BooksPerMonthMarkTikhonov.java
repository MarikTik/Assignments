/**
This program demonstrates how a cast operator
can be used to prevent integer division.
*/
public class BooksPerMonthMarkTikhonov
{
    public static void books( )
    {
        int books = 15, // Number of books to read
        months = 6; // Number of months to read them
        double booksPerMonth; // Average books per month
        // Display the number of books I plan to
        // read and the number months in which I
        // plan to read them.
        System.out.print("I plan to read ");
        System.out.print(books + " books in ");
        System.out.println(months + " months.");
        // Calculate the average books per month.
        booksPerMonth = (double) books / months;
        // Display the average number of books per month.
        System.out.print("I will read an average of ");
        System.out.print(booksPerMonth);
        System.out.println(" books per month.");
        Draw draw = new Draw();
        draw.setCanvasSize(400, 400);
        draw.setXscale(0, 400);
        draw.setYscale(0, 400);
        draw.clear(Draw.GREEN);
        draw.setPenColor(Draw.BLACK);
        draw.text(200, 300, "I plan to read " + books + " books in " + months + " months ");
        draw.text(150, 250, "I will read an average of " + booksPerMonth +
            " books per month. ");
    }
    public static void main(String []args){
        books();
    }
}
// Expected output ============
//I plan to read 15 books in 6 months.
//I will read an average of 2.5 books per month.