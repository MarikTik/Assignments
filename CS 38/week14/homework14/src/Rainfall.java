import java.util.Scanner;

public class Rainfall {

    // This class was added because the ill written directions of the question 
    private static class Month{
        private String _name;

        private double _rain;

        public Month(String name, double rain){
            _name = name;
            _rain = rain;
        }

        public double rain(){
            return _rain;
        }
        public String toString(){
            return _name;
        }
    }
        
    private Month[] _dataPoints = new Month[12];

    private static final String[] _monthNames = new String[]{
        "Jan", "Feb", "Mar", "Apr", "May",
        "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    ///accepts doubles as 
    public Rainfall(Scanner stream){
        for (int i = 0; i < 12; i++){
            var value = stream.nextDouble();
            if (value < 0) 
                i--;
            else _dataPoints[i] = new Month(_monthNames[i], value);
        }
    }

    public double total(){
        double t = 0;
        for (int i = 0; i < _dataPoints.length; i++)
            t =+ _dataPoints[i].rain();
        return t;
    }

    public double average(){
        return total() / _dataPoints.length;
    }

    //returns the month with the biggest amount of rain
    public Month max(){
        double m = _dataPoints[0].rain();
        int index = 0;
        for (int i = 1; i < _dataPoints.length; i++)
            if (m < _dataPoints[i].rain()){
                index = i;
                m = _dataPoints[i].rain();
            }
        return _dataPoints[index];
    }

    /// returns the month with the least rain
    public Month min(){
        double m = _dataPoints[0].rain();
        int index = 0;
        for (int i = 1; i < _dataPoints.length; i++)
            if (m > _dataPoints[i].rain()){
                index = i;
                m = _dataPoints[i].rain();
            }

        return _dataPoints[index];
    }

    public static void demo(){
        var stream = new Scanner(System.in);
        Rainfall rainfall = new Rainfall(stream);

        System.out.printf("Total amount of rain last year: %f\n", rainfall.total());
        System.out.printf("Average amount of rain last year: %f\n", rainfall.average());
        System.out.printf("Month with the highest amount of rain: %s\n", rainfall.max());
        System.out.printf("Month with the lowest amount of rain: %s\n", rainfall.min());
        stream.close();
    }
}

