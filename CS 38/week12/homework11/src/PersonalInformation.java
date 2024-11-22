import java.awt.Font;

public class PersonalInformation {
     public PersonalInformation(String name, String address, String phoneNumber, int age) {
          this.name = name;
          this.address = address;
          this.phoneNumber = phoneNumber;
          this.age = age;
     }

     public String getName() {
          return name;
     }
     public void setName(String name) {
          this.name = name;
     }

     public String getAddress() {
          return address;
     }
     public void setAddress(String address) {
          this.address = address;
     }

     public String getPhoneNumber() {
          return phoneNumber;
     }

     public void setPhoneNumber(String phoneNumber) {
          this.phoneNumber = phoneNumber;
     }

     public int getAge() {
          return age;
     }

     public void setAge(int age) {
          this.age = age;
     }

     public String toString(){
          return String.format("Name: %s \nAddress: %s \nPhone Number: %s \nAge: %d", name, address, phoneNumber, age);
     }

     public static void demo(){
          var info1 = new PersonalInformation("John Doe", "123 Main St", "555-555-5355", 30);
          var info2 = new PersonalInformation("Chopper", "456 Elm St", "555-555-3333", 25);
          var info3 = new PersonalInformation("Mark", "789 Oak St", "555-555-1113", 35);

          System.out.printf("%s\n\n%s\n\n%s\n", info1, info2, info3);
          var screen = Form.defaultForm();
          screen.setFont(new Font("Arial", Font.PLAIN, 8));
          screen.text(200, 100, info1.toString());
          screen.text(200, 200, info2.toString());
          screen.text(200, 300, info3.toString());
     }
     private String name;
     private String address;
     private String phoneNumber;
     private int age;
}
