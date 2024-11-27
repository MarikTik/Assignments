import java.awt.Color;
import java.util.Random;

public class ColorUtil {

    /// returns a shifted color closer to the target
    public static Color shift(Color from, Color to){
        int redShift, greenShift, blueShift;
        if (from.getRed() > to.getRed())
            redShift = from.getRed() - 1;
        else if (from.getRed() < to.getRed())
            redShift = from.getRed() + 1;
        else redShift = from.getRed();

        if (from.getGreen() > to.getGreen())
            greenShift = from.getGreen() - 1;
        else if (from.getGreen() < to.getGreen())
            greenShift = from.getGreen() + 1;
        else greenShift = from.getGreen();

        if (from.getBlue() > to.getBlue())
            blueShift = from.getBlue() - 1;
        else if (from.getBlue() < to.getBlue())
            blueShift = from.getBlue() + 1;
        else blueShift = from.getBlue();

        return new Color(
            redShift,
            greenShift,
            blueShift      
        );
    }   

    public static boolean same(Color c1, Color c2){
        return c1.getRGB() == c2.getRGB();
    }

    public static Color randomLightColor(){
        return new Color(
            rand.nextInt(60, 240),
            rand.nextInt(60, 240),
            rand.nextInt(60, 240)
        );
    }

    private static Random rand = new Random();
}
