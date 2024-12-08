public class Program {
    public static void displayElementsBiggerThen(int [] arr, int value){
        for (int v : arr)
            if (v > value)
                System.out.println(v);
    }
    public static void main(String []args){
        //Rainfall.demo();
        ChargeAccountValidator.demo();
        displayElementsBiggerThen(new int[]{1,2,3,4,5,6,7,8,9}, 5); // prints all elements bigger then 5
    }
}
