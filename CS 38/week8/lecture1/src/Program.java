import java.awt.Font;

public class Program {
    private static final int width = 400, height = 400;
    public static double sine_wave(double x, double amplitude, double period, double xShift, double verticalShift){
        return amplitude * Math.sin((Math.PI * 2) / period * x + xShift) + verticalShift;
    }
    public static double tangent_line(double x, double amplitude, double period, double xShift, double verticalShift){
        return amplitude * Math.tan((Math.PI * 2) / period * x + xShift) + verticalShift;
    }
    public static void main(String []args){
        Function sine = (x, p) -> sine_wave(x, p[0], p[1], p[2], p[3]);
        Function tangent = (x, p) -> tangent_line(x, p[0], p[1], p[2], p[3]);

        var form = new Form(
            width,
            height, 
            Draw.WHITE,
            Draw.BLACK,
            new Font("Arial", Font.PLAIN, 24),
            "tangent function sketch"
        ).create();
        var graph = new Graph(form, width, height, true);
        graph.sketch(tangent, 100,50 , 0, 200);
    }
}
