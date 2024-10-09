/**A general interface for a function that accetps a variable x, and variable number of parameters**/
public interface Function{
    /**
    * method template for computable functions of the form f(x, p1, p2, ..., pn)
    * @arg variable - the dependant variable of the function
    * @arg parameters - sequence of independant variables of the function.
    **/
    public double compute(double variable, double... parameters);
}
