import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.stream.Collector;
import java.util.stream.Collectors;
/**
 * Description
 * class with all the required methods for the current lecture 
 * 
 * @author Mark Tikhonov
 * @version 0.0.1
 */
public class Program {
    public static void readFileBasic() throws IOException{
        File file = new File("week8/lecture2/data.txt");
        Scanner scanner = new Scanner(file);
        while (scanner.hasNextLine())
            System.out.println(scanner.nextLine());
        scanner.close();
    }

    
    public static void main(String []args){
        try{
            var students = Student.fromFile("week8/lecture2/data.txt");
           

            Student topStudent = students.stream().reduce(
                new Student("0", 0, 0.0, "Invalid"),    
            (student1, student2) ->
                student1.GPA > student2.GPA ? student1 : student2
            );

            
            double averageGPA = students.stream()
                .map(student -> student.GPA)
                .reduce(0.0, (gpa1, gpa2) -> gpa1 + gpa2) / students.size();

            System.out.println(topStudent);
            System.out.println(averageGPA);
            

        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    } 
}
