
/**
 * Description
 * A circle class implemented by the assignment directions
 *  
 * @author Mark
 * @version 0.0.1
 */
public class Circle
{
     
    public Circle(double radius, boolean isSolid)
    {
        this.radius = radius;
        this.isSolid = isSolid;
    }
    public double getDiameter()
    {
        return 2 * radius;
    }

    public double getCircumference()
    {
        return 2 * PI * radius;
    }
 
    public void setRadius(double newValue)
    {
        radius = newValue;
    }   

    public void DrawMe(Draw screen){
        if (isSolid)
            screen.filledCircle(200, 200, radius);
        else
            screen.circle(200, 200, radius);
    }


    public double getRadius()
    {
        return radius;
    }

    public String toString()
    {
        String msg = "QQQ"; // what's the point?
        return msg;
    }
    private double radius;
    private double PI = 3.14159;
    private boolean isSolid;
}