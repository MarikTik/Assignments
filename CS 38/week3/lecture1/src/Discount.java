
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
        discount = 11.8;
        // Calculate the sale price by subtracting
        // the discount from the regular price.
        salePrice = 47.2;
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