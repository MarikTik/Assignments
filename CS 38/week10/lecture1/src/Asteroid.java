import java.io.File;

public class Asteroid {
    public Asteroid(Draw screen, int width, int height){
        this.screen = screen;
        this.width = width;
        this.height = height;
    }

    public void show(double x, double y){
        File file = new File("week10/lecture1/assets/asteroid3.png");
        if (file.exists()){
            System.out.println("exists");
        }
        else System.out.println("doesn't exist");
        screen.picture(x, y, "week10/lecture1/assets/asteroid3.png", width, height);
    }

    private Draw screen;
    private int width, height;
}
