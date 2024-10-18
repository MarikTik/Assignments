import java.awt.Color;
import java.util.Random;


class Cookie{
    public Cookie(Draw screen, double xCenter, double yCenter, double radius){
        this.screen = screen;
        this.xCenter = xCenter;
        this.yCenter = yCenter;
        this.radius = radius;
    }

 

    public BitableCookie show(int chockolateChips){
        double offset = radius / 30.0; // this is an arbitrary choice
        screen.setPenColor(cookieBorderColor);
        screen.filledCircle(xCenter, yCenter, radius);
        screen.setPenColor(cookieFillColor);
        double x = xCenter - offset, y = yCenter - offset, r = radius - offset;
        screen.filledCircle(x, y, r);
        screen.setPenColor(chockolateChipColor);

        double chipRadius = r / 15;

        for (int i = 0; i < chockolateChips; i++){
            
            double randX = rand.nextDouble(x - r + chipRadius + offset, x + r - chipRadius - offset);
            double sr = Math.sqrt(Math.pow(r, 2) - Math.pow((randX - x), 2));
            double randY = rand.nextDouble(y - sr + chipRadius, y + sr - chipRadius);

            screen.filledCircle(randX, randY, chipRadius);
        }
        return new BitableCookie(screen);
    }

    private Draw screen;
    private double xCenter, yCenter, radius;

    private Random rand = new Random();
    private final Color cookieFillColor = new Color(205, 133, 63);
    private final Color chockolateChipColor = new Color(90, 35, 15);
    private final Color cookieBorderColor = new Color(139, 69, 19);

    public static class BitableCookie{

        public void bite(double x, double y, double bite_radius, Color fillColor){
            screen.setPenColor(fillColor);
            screen.filledCircle(x, y, bite_radius);
        }

        private BitableCookie(Draw screen){
            this.screen = screen;    
        }
        private Draw screen;
    }
}