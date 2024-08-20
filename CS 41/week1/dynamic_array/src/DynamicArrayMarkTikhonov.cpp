#include <iostream>

int main(){
     size_t capacity;
     std::cout << "enter array capacity: ";
     std::cin >> capacity;
     double *array = new double[capacity];
     size_t index = 0;

     for (; index < capacity; index++){
          std::cout << "enter value: ";
          std::cin >> array[index];
          if (array[index] == -1) break;
     }

     std::cout << "\"the list\": {";
     for (size_t i = 0; i < index; i++)
          std::cout << array[i] << ", ";
     std::cout << "\b\b}\n";
     delete [] array;
}