import java.awt.Color;
import java.awt.Font;

public class Form{
    public int width;
    public int height;
    public Color backgroundColor;
    public Color penColor;
    public Font font;
    public String title;

    public Form(int width, int height, Color backgroundColor, Color penColor, Font font, String title){
        this.width = width;
        this.height = height;
        this.backgroundColor = backgroundColor;
        this.penColor = penColor;
        this.font = font;
        this.title = title;
    }
    public Draw create(){
        Draw screen = new Draw();
        //scaling the screen
        screen.setCanvasSize(width, height);
        screen.setXscale(0, width);
        screen.setYscale(height, 0);
        screen.setTitle(title);
        screen.clear(backgroundColor);
        screen.setFont(font);  
        screen.setPenColor(penColor);
        return screen;
    }
}
