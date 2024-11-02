import java.awt.Color;
import java.awt.Font;

/**
 * Represents a board consisting of a grid of polygons, with customizable color and text rendering.
 */
public class Board {
    /**
     * Constructs a Board with the specified polygon and grid size.
     *
     * @param polygon the Polygon2D object representing a single tile in the grid
     * @param n the number of rows and columns in the grid
     */
    public Board(Polygon2D polygon, int n){
        this.polygon = polygon;
        this.n = n;
    }

    
    /**
     * Renders the board on the specified drawing screen. Each polygon in the grid can be
     * individually colored and labeled based on the color and text predicates, if set.
     *
     * @param screen the Draw object to render the board on
     */
    public void show(Draw screen){
        Color saveColor = screen.getPenColor();
        Font saveFont = screen.getFont();   
        Polygon2D savePolygon = polygon;

    
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                Point center = polygon.center();
                if (colorPredicate != null)
                    screen.setPenColor(colorPredicate.colorAt(center));
                
                polygon.showFilled(screen);

                if (textPredicate != null){
                    screen.setFont(textPredicate.fontAt(center));
                    screen.setPenColor(textPredicate.textColorAt(center));
                    screen.text(center.getX(), center.getY(), textPredicate.textAt(center));
                }
                polygon = polygon.translate(0, polygon.getHeight());
            
            }
            polygon = polygon.translate(polygon.getWidth(), n * -polygon.getHeight());
        }
        polygon = savePolygon;
        screen.setPenColor(saveColor);
        screen.setFont(saveFont);
    }

    /**
     * Sets the text predicate for rendering text within each polygon's center.
     * The text predicate defines the font, color, and content of the text displayed
     * in each tile.
     *
     * @param textPredicate the ITextPredicate used to define text attributes in each tile
     */
    public void setTextPredicate(ITextPredicate textPredicate){
        this.textPredicate = textPredicate;   
    }

    /**
     * Sets the color predicate for rendering the color of each polygon in the grid.
     * The color predicate defines the color for each tile based on its center position.
     *
     * @param colorPredicate the IColorPredicate used to define color attributes in each tile
     */
    public void setColorPredicate(IColorPredicate colorPredicate){
        this.colorPredicate = colorPredicate;
    }

    private ITextPredicate textPredicate = null;
    private IColorPredicate colorPredicate = null;
    private int n;
    private Polygon2D polygon;
}
