import java.awt.Color;
import java.awt.Font;

public interface ITextPredicate {
     public String textAt(Point p);
     public Color textColorAt(Point p);
     public Font fontAt(Point p);
}
