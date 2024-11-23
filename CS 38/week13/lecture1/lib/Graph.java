/**Graphing utility to sketch single variable functions on Draw canvas**/
public class Graph{
    public Graph(Draw form, int width, int height, boolean reverse){
        this._form = form;
        this._width = width;
        this._height = height;
        this._reverse = reverse;
    }
    public void setWidth(int width){
        this._width = width;
    }
    public void setHeight(int height){
        this._height = height;
    }
    public void setReverse(boolean reverse){
        this._reverse = reverse;
    }
    public void sketch(Function f, double... parameters){
        double xShift = 0.05;
        for (double x = 0, y = f.compute(x, parameters); 
            x <= _width;
            x += xShift, y = f.compute(x, parameters))
        {
            if (_reverse)
                y = _height - y;
            _form.point(x, y);
        }
    }
     

    private Draw _form;
    private int _width;
    private int _height;
    private boolean _reverse;
}