/**
* Represents a 2D polygon with a center point and corner points.
*/
public class Polygon2D {

    /**
     * Constructs a Polygon2D from an array of points.
     *
     * @param points the array of points defining the polygon
     */
    public Polygon2D(Point[] points){
        pointsX = new double[points.length];
        pointsY = new double[points.length];
        int i = 0;
        for (var point : points){
            pointsX[i] = point.getX();
            pointsY[i] = point.getY();
            i++; 
        }

        double maxX = max(pointsX);
        double minX = min(pointsX);
        double maxY = max(pointsY);
        double minY = min(pointsY);

     
        corners[0] = new Point(pointsX[indexOf(pointsY, maxY)], maxY);
        corners[1] = new Point(maxX, pointsY[indexOf(pointsX, maxX)]);
        corners[2] = new Point(pointsX[indexOf(pointsY, minY)], minY);
        corners[3] = new Point(minX, pointsY[indexOf(pointsX, minX)]);

        center = new Point((maxX + minX) / 2, (maxY + minY) / 2);
    }   

    /**
     * Returns an array of points representing the corners of the polygon.
     * The points are ordered clockwise starting from the topmost corner.
     *
     * @return an array of corner points
     */
    public Point[] corners(){
       return this.corners;
    }
    
    /**
     * Returns the center point of the polygon.
     *
     * @return the center point
     */
    public Point center(){
        return this.center;
    }

    /**
     * Translates the polygon by the specified distances along the x and y axes.
     *
     * @param dx the distance to translate along the x-axis
     * @param dy the distance to translate along the y-axis
     * @return a new Polygon2D translated by the specified distances
     */
    public Polygon2D translate(double dx, double dy){
        Point[] newPoints = new Point[pointsX.length];
        for (int i = 0; i < pointsX.length; i++){
            newPoints[i] = new Point(pointsX[i] + dx, pointsY[i] + dy);
        }
        return new Polygon2D(newPoints);
    }

    /**
     * Scales the polygon by the specified factor.
     *
     * @param factor the scaling factor
     * @return a new Polygon2D scaled by the specified factor
     */
    public Polygon2D scale(double factor){
        Point[] newPoints = new Point[pointsX.length];
        for (int i = 0; i < pointsX.length; i++){
            newPoints[i] = new Point(pointsX[i] * factor, pointsY[i] * factor);
        }
        return new Polygon2D(newPoints);
    }

    /**
     * Returns the width of the polygon, calculated as the distance
     * between the leftmost and rightmost corners.
     *
     * @return the width of the polygon
     */
    public double getWidth(){
        return corners[1].getX() - corners[3].getX();
    }

    /**
     * Returns the height of the polygon, calculated as the distance
     * between the topmost and bottommost corners.
     *
     * @return the height of the polygon
     */
    public double getHeight(){
        return corners[0].getY() - corners[2].getY();
    }

    /**
     * Renders the polygon on the specified drawing screen.
     *
     * @param screen the drawing screen to render on
     */
    public void show(Draw screen){
        screen.polygon(pointsX, pointsY);
    }

    /**
     * Renders the polygon as a filled shape on the specified drawing screen.
     *
     * @param screen the drawing screen to render on
     */
    public void showFilled(Draw screen){
        screen.filledPolygon(pointsX, pointsY);
    }

    /**
     * Finds the maximum value in the specified array.
     *
     * @param arr the array of values
     * @return the maximum value in the array
     */
    private static double max(double[] arr){
        double max = arr[0];
        for (var elem : arr){
            if (elem > max)
                max = elem;
        }
        return max;
    }

    /**
     * Finds the minimum value in the specified array.
     *
     * @param arr the array of values
     * @return the minimum value in the array
     */
    private static double min(double[] arr){
        double min = arr[0];
        for (var elem : arr){
            if (elem < min)
                min = elem;
        }
        return min;
    }

    /**
     * Returns the index of the specified element in the array, or -1 if not found.
     *
     * @param arr the array to search
     * @param elem the element to find
     * @return the index of the element, or -1 if not found
     */
    private static int indexOf(double[] arr, double elem){
        for (int i = 0; i < arr.length; i++){
            if (arr[i] == elem)
                return i;
        }
        return -1;
    }

    private Point center;
    private Point[] corners = new Point[4];
    private double[] pointsX;
    private double[] pointsY;
}
