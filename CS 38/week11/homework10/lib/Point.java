public class Point {
    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }
    public double getX(){
        return x;
    }
    public double getY(){
        return y;
    }
    public void setX(double newX){
        x = newX;
    }
    public void setY(double newY){
        y = newY;
    }

    public String toString(){
        return String.format("(%f, %f)",x, y);
    }
    private double x;
    private double y;
}
