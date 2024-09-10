#include <iostream>
#include <algorithm>
#include <string>

template <typename T>
class graph_matrix{
     public:
          graph_matrix(size_t n)
               : _matrix(new T*[n]), _size(n)
          {
               for (size_t i = 0; i < _size; i++) 
               {
                    _matrix[i] = new T[n]();
               }
          }

          void link(size_t x, size_t y){
               _validate_link(x, y);
               _matrix[x][y] = 1;
          }

          bool at(size_t x, size_t y) const{
               _validate_link(x, y);
               return _matrix[x][y];
          }

          size_t size() const{
               return _size;
          }

          ~graph_matrix(){
               for (size_t i = 0; i < _size; i++) delete[] _matrix[i];
               delete[] _matrix;
          }
          
     private:
          void _validate_link(size_t x, size_t y) const{
               if (x >= _size || y >= _size) {
                    throw std::out_of_range("Index out of bounds");
               }
          }
          T **_matrix;
          size_t _size;
};

template<typename T, typename U>
class labeled_graph_matrix{
     public:
          labeled_graph_matrix(size_t n) 
               : _matrix{n},
                _labels(new U[n]),
                _begin(_labels),
                _end(_labels + n)
          {
          }

          void label_vertex(size_t position, const U& label){
               _labels[position] = label;
          }

          bool link_vertex(const U& labeled_vertex_a, const U& labeled_vertex_b){
               U *vertex_a = std::find(_begin, _end, labeled_vertex_a);
               U *vertex_b = std::find(_begin, _end, labeled_vertex_b);

               if (vertex_a == _end or vertex_b == _end)
                    return false;
               
               _matrix.link(vertex_a - _begin, vertex_b - _begin);
               return true;
          }

          friend std::ostream& operator << (std::ostream &os, const labeled_graph_matrix<T, U>& graph_matrix){
               const auto &matrix = graph_matrix._matrix;
               size_t size = matrix.size();

               for (size_t i = 0; i < size; i ++)
                    for (size_t j = 0; j < size; j ++)
                         if (matrix.at(i, j))
                              os << graph_matrix._labels[i] << graph_matrix._labels[j] << ", ";
               os << "\b\b";
               return os;
          }

          ~labeled_graph_matrix(){
               delete[] _labels;
          }
          
     private:
          graph_matrix<T> _matrix;
          U *_labels = nullptr, *_begin, *_end;
};
int main(){
     size_t verticies;
     std::cout << "Enter amount of verticies: ";
     std::cin >> verticies;

     labeled_graph_matrix<int, std::string> matrix(verticies);

     for (size_t i = 0; i < verticies; i++){
          std::string label;
          std::cout << "Label vertex " << (i + 1) << ": ";
          std::cin >> label;
          matrix.label_vertex(i, label);
     }

     std::cout << "Define an edge by listing a pair of vertices, i.e. \"A B\", or -1 to stop:\n";

     while(true){
          std::string vertex_a, vertex_b;
          std::cin >> vertex_a;
          if (vertex_a == "-1") break;
          std::cin >> vertex_b;
          std::cout << "Added edge " << vertex_a << "->" << vertex_b << "\n";

          if (not matrix.link_vertex(vertex_a, vertex_b))
               throw std::runtime_error("invalid label");          
     }

     std::cout << "Your edges are: " << matrix;
}