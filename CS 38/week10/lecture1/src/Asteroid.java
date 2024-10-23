import java.io.File;

public class Asteroid {
    public Asteroid(Draw screen, int width, int height){
        this.screen = screen;
        this.width = width;
        this.height = height;
    }

    public void show(double x, double y){
       
    
        screen.picture(x, y, "assets/asteroids/large/a10000.png", width, height);
    }

    private Draw screen;
    private int width, height;
}
