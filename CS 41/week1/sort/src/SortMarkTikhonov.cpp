#include <iostream>
#include <array>

template <typename T, size_t N>
void sort(std::array<T, N> &array){ //most basic O(n^2) sort function
     for (size_t i = 0; i < N; i++)
          for (size_t j = i + 1; j < N; j++)
               if (array[j] < array[i])
                    std::swap(array[j], array[i]);
}

template <typename T, size_t N>
void print_array(const std::array<T, N> &array)
{
     if (not N)
          return;
     std::cout << '{';
     std::cout << array[0];
     for (size_t i = 1; i < N; i++)
          std::cout << ", " << array[i];
     
     std::cout << '}';
}

int main(){
     std::array<int, 5> array = {5,1,6,0,-1};
     sort(array);
     print_array(array);
}