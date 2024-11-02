
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class Polygon2D {
    public Polygon2D(Point[] points){
        pointsX = new double[points.length];
        pointsY = new double[points.length];
        int i = 0;
        for (var point : points){
            pointsX[i] = point.getX();
            pointsY[i] = point.getY();
            i++; 
        }
           
    }   
    public Point[] corners(){
        double xMin = Collections.min(pointsX);
        double yMin = Collections.min(pointsY);
        double xMax = Collections.max(pointsX);
        double yMax = Collections.max(pointsY);

      
    }

    public void show(Draw screen){
        screen.polygon(pointsX, pointsY);
    }
    public void showFilled(Draw screen){
        screen.filledPolygon(pointsX, pointsY);
    }
    private double[] pointsX;
    private double[] pointsY;
}
