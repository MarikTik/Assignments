import java.util.Random;

class Lecture1{
    public static void main(String []args){
        Draw draw = new Draw();
        double width = 1920, height = 1080;
        draw.setCanvasSize((int)width, (int)height);
        draw.setXscale(0, width);
        draw.setYscale(0, height);
        draw.clear(Draw.BLACK);
        
        
        Random rand = new Random();
       
        for (double y = 0; y < height; y += 13)
        {   
            draw.setPenColor(rand.nextInt(0, 255), rand.nextInt(0, 255), rand.nextInt(0, 255));
            draw.text(rand.nextDouble(0, width), y, "hello world");
        }
        
        
       
    }
}