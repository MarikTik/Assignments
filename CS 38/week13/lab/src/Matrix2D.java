import java.util.ArrayList;
import java.lang.IllegalArgumentException;
import java.lang.IndexOutOfBoundsException;

public class Matrix2D<T> {
    public Matrix2D(int width, int height){
        if (width < 1 || height < 1)
            throw new IllegalArgumentException(
                String.format("Cannot initialize 2D matrix with dimension of size [%d, %d]",
                width, height)
            );

        _width = width;
        _height = height;
        int capacity = width * height;
        _matrix = new ArrayList<>(capacity);
        for (int i = 0; i < capacity; i ++)
            _matrix.add(null);
        
    }

    public Matrix2D(T [][]array2D){
        _height = array2D.length;
        _width = array2D[0].length;
        _matrix = new ArrayList<>(_width * _height);

     
        for (T[] arr : array2D)
        {
            if (arr.length != _width)
                throw new IllegalArgumentException("Cannot initialize 2D matrix with inconsistent row sizes");

            for (T item : arr)
                _matrix.add(item);
        }            
    }

    public T get(int row, int col){
        return _matrix.get(row * _width + col);
    }

    public void set(int row, int col, T value){
        _matrix.set(row * _width + col, value);
    }

  
    public int width(){
        return _width;
    }
    public int height(){
        return _height;
    }

    public void fill(T value){
        for (int i = 0 ; i < _matrix.size(); i ++)
            _matrix.set(i, value);
    }

    public String toString(){
        String repr = "";
        for (int i = 0; i < _height; i++){
            for (int j = 0; j < _width; j++)
                repr += get(i, j) + " ";
            repr += "\n";
        }
        return repr;
    }
    private int _width, _height;
    public ArrayList<T> _matrix;
}
