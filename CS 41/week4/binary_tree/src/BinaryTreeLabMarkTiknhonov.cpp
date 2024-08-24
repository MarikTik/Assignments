#include <iostream>
#include <ostream>

template<typename T, size_t N> 
class binary_tree{

     public:
          void add(T value){
               if (_count == N)
                    throw std::overflow_error("binary tree memory overflow");

               _data[_count++] = value;
          }

          friend std::ostream &operator << (std::ostream &os, binary_tree<T, N> &tree){
               tree.print_vlr(os, 0);
               return os;
          }
     private:
          void print_vlr(std::ostream &os, size_t index){

               if (index >= _count)
                    return;

               os << _data[index] << " ";
               print_vlr(os, 2 * index + 1); // printing left subtree
               print_vlr(os, 2 * index + 2); // printing right subtree
          }

          T _data[N];
          size_t _count = 0;
};

int main(){
     binary_tree<int, 100> tree;

     for (int i = 0; i < 100; i ++)
          tree.add(i);

     std::cout << tree;
}