/**
 * Represents a point in a 2D coordinate system.
 */
public class Point {
    /**
    * Constructs a point with the specified x and y coordinates.
    *
    * @param x the x-coordinate of the point
    * @param y the y-coordinate of the point
    */
    public Point(double x, double y){
        this.x = x;
        this.y = y;
    }

    /**
     * Gets the x-coordinate of the point.
     *
     * @return the x-coordinate
     */
    public double getX(){
        return x;
    }

    /**
     * Gets the y-coordinate of the point.
     *
     * @return the y-coordinate
     */
    public double getY(){
        return y;
    }

    /**
     * Sets the x-coordinate of the point.
     *
     * @param newX the new x-coordinate
     */
    public void setX(double newX){
        x = newX;
    }

    /**
     * Sets the y-coordinate of the point.
     *
     * @param newY the new y-coordinate
     */
    public void setY(double newY){
        y = newY;
    }

    /**
     * Returns a string representation of the point in the format "(x, y)".
     *
     * @return a string representation of the point
     */
    public String toString(){
        return String.format("(%f, %f)",x, y);
    }
    private double x;
    private double y;
}
