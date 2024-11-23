import java.util.function.Function;
import java.util.function.Consumer;
import java.util.function.Supplier;
import java.io.Serial;
import java.util.function.BiFunction;

public class Program {
    public static void main(String []args){
        Function<Double[], Double> sum = (variables) -> {
            double s = 0;
            for (double variable : variables) s += variable;
            return s;
        };  
        System.out.println(sum.apply(new Double[]{10.0, 20.0, 30.0}));
         
      
    }
}