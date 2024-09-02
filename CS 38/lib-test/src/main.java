//import java.awt.Color;
class Main{
    public static void main(String []args)
    {
        Draw screen = new Draw();
    
        int width = 1920;
        int height = 1080;
        screen.setCanvasSize(width, height);
    

        screen.clear(Draw.BLACK);
     
        
        double circleRadius = 0.01;
        double circle1Y = 0.2;
        double circle2Y = 0.5;
        while(true){
            double shift = circleRadius / 10;
             for (double i = circleRadius; i < 1; i+=shift)
            {   
                // drawing circle 1
                screen.setPenColor(Draw.GREEN);
                screen.filledCircle(i, i, circleRadius);
                // drawing circle 2                
                // screen.setPenColor(Draw.YELLOW);
                // screen.filledCircle(2 - 0.05 - i, circle2Y, circleRadius);
                
                //screen.pause(10); // ~24 fps delay
                
                // clear trace
                screen.setPenColor(Draw.BLACK);

                screen.filledCircle(i - shift, i - shift, circleRadius);
                //screen.filledCircle(2 - i, circle2Y, circleRadius);
                
            }
        }
        
    }
}
 