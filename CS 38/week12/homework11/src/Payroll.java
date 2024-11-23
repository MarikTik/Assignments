import java.util.Scanner;

public class Payroll {
     public Payroll(String name, int ID) {
          this.name = name;
          this.ID = ID;
     }

     public String getName() {
          return name;
     }
     public void setName(String name) {
          this.name = name;
     }

     public int getID() {
          return ID;
     }
     public void setID(int ID) {
          this.ID = ID;
     }

     public double getHourlyRate() {
          return hourlyRate;
     }

     public void setHourlyRate(double hourlyRate) {
          this.hourlyRate = hourlyRate;
     }

     public double getHoursWorked() {
          return hoursWorked;
     }

     public void setHoursWorked(double hoursWorked) {
          this.hoursWorked = hoursWorked;
     }

     public double getGrossPay() {
          return hourlyRate * hoursWorked;
     }    

     public static void demo(){
          Payroll payroll = new Payroll("John Doe", 12345);
          Scanner scanner = new Scanner(System.in);
          System.out.print("Enter hourly rate: ");
          payroll.setHourlyRate(scanner.nextDouble());
          System.out.print("Enter hours worked: ");
          payroll.setHoursWorked(scanner.nextDouble());
          String output = String.format("Gross pay of %s (ID=%d) is %.2f", payroll.name, payroll.ID, payroll.getGrossPay());
          System.out.println(output);
          Form.defaultForm().text(200, 200, output);
          scanner.close();
     }
     private String name; 
     private int ID;
     private double hourlyRate;
     private double hoursWorked;
}

// Design a Payroll class that has fields for an employee’s name, ID number, hourly pay
// rate, and number of hours worked. Write the appropriate accessor and mutator meth-
// ods and a constructor that accepts the employee’s name and ID number as arguments.
// The class should also have a method that returns the employee’s gross pay, which is
// calculated as the number of hours worked multiplied by the hourly pay rate. Write a
// program that demonstrates the class by creating a Payroll object, then asking the user
// to enter the data for an employee. The program should display the amount of gross pay
// earned.