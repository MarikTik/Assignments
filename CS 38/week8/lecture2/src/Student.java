import java.io.IOException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;


public class Student {
    public Student(String ID, int grade, double GPA, String name){
        this.ID = ID;
        this.grade = grade;
        this.GPA = GPA;
        this.name = name;
    }
    public static List<Student> fromFile(String path) throws IOException{
        return fromFile(new File(path));
    }
    public static List<Student> fromFile(File file) throws IOException{
        var students = new ArrayList<Student>();
        Scanner scanner = new Scanner(file);
        while(scanner.hasNextLine()){
            String line = scanner.nextLine();
            var split = line.split(",");
            var ID = split[0].trim().split("d")[1];
            var grade = Integer.parseInt(split[1].trim().split("th")[0]);
            var GPA =  Double.parseDouble(split[2].trim().split(":")[1]);
            var name = split[3].split(": ")[1].trim();
            students.add(new Student(ID, grade, GPA, name));
        }
        scanner.close();
        return students;
    }
    
    public String toString(){
        return String.format("ID: %s\tgrade: %dth\tGPA: %f\tname: %s", ID, grade, GPA, name);
    }

    public final String ID;
    public final int grade;
    public final double GPA;
    public final String name;


}