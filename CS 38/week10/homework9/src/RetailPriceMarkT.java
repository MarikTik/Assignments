public class RetailPriceMarkT {

     public static void retailPriceCalculator(){
          System.out.print("Enter the wholesale cost: ");
          double wholesaleCost = Double.parseDouble(scanner.next());
          System.out.print("Enter the markup percentage: ");
          double markupPercentage = Double.parseDouble(scanner.next());
          double retailPrice = wholesaleCost + (wholesaleCost * markupPercentage / 100);
          System.out.printf("The retail price is %.2f\n", retailPrice);
          defaultForm.create().text(width / 2, height / 2, "The retail price is " + retailPrice);
     }
}
