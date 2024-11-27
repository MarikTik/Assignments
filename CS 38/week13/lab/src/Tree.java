import java.awt.Color;
import java.util.Random;

public class Tree {
    public Tree(Draw screen, double x, double y, double width, double height){
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.screen = screen;
        // leaves = new Triangle();
        updateStem();
        updateLeaves();
        generateOrnaments();
    }

    public void update(){
        
    }

    public void setStemColor(Color color){
        stemColor = color;
        updateStem();
    }
    public void setLeafColor(Color color){
        leafColor = color;
        updateLeaves();
    }

    private void updateStem(){
        double stemWidth = width * 0.3;
        double stemheight = height * 0.3;

        screen.setPenColor(stemColor);
        screen.filledRectangle(x, y - stemheight / 2, stemWidth / 2, stemheight / 2);
    }

    private void updateLeaves(){
        screen.setPenColor(leafColor);
        screen.filledPolygon(
            new double[]{
                x - width / 2, x + width / 2, x
            },
            new double[]{
                y - height * 0.3, y - height * 0.3, y - height
            });
    }

    private void updateOrnaments(){
        ornaments = new Ornament[rand.nextInt(3, 10)];
    }
    public void generateOrnaments(){

    }

  

    private Color leafColor = new Color(1, 50, 32);
    private Color stemColor = new Color(53, 33, 0);

    private double x, y, width, height;
    private Triangle leaves;
    private Ornament[] ornaments;
    private Draw screen;
    private static Random rand = new Random();
}
