import java.awt.Color;
import java.util.Random;
///Ornament by Mark Tikhonov, functionality extended and method names normalized
public class Ornament {
    public Ornament(Draw screen, int x, int y, int radius){
        this.screen = screen;
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    public void update(){
        if (ColorUtil.same(currentColor, targetColor))
            targetColor = ColorUtil.randomLightColor();
        
        else currentColor = ColorUtil.shift(currentColor, targetColor);

        screen.setPenColor(currentColor);
        screen.filledCircle(x, y, radius);
    }
    
    private int x, y, radius;
    private Draw screen;
    Color currentColor = ColorUtil.randomLightColor();
    Color targetColor = ColorUtil.randomLightColor();
}
