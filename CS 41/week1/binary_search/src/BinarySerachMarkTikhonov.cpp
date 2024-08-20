#include <iostream>
#include <array>
#ifdef __unix__
     #include <unistd.h> // this header has _POSIX_VERSION defined to guarantee the existance of ssize_t
#endif

#ifdef _POSIX_VERSION
     #include <sys/types.h>
     using index_t = ssize_t;
#else
     using index_t = long; 
     // I could use long in both cases but there is no guarantee that it's not 4 bytes on on 64 bit platform.
     // ssize_t guarantees that it's the same size as size_t.
#endif

// there might be a better implementation, but that's what I came up with
template <typename T, size_t N>
index_t binary_search(const std::array<T, N> &sorted_array, T target){
     index_t left_i = 0, right_i = sorted_array.size() - 1; // will overflow if size exceeds 2^63 - 1 (hopefully not in this course)
     index_t middle_i = (left_i + right_i) / 2;
     
     while (sorted_array[middle_i] not_eq target and left_i not_eq middle_i){
          if(sorted_array[middle_i] < target)  
               left_i = middle_i;
          else 
               right_i = middle_i;

          middle_i = (left_i + right_i) / 2;
     }
     if (sorted_array[middle_i] == target) 
          return middle_i;
     
     if (sorted_array[right_i] == target) // the rightmost element is not checked in the loop so I do it explicitly
          return right_i;

     return -1;
}


// sample program
int main(){
     std::array<int, 8> array = {1, 2, 4, 5, 6, 7, 8, 9};
     std::cout << binary_search(array, 1) << std::endl;
     std::cout << binary_search(array, 2) << std::endl;
     std::cout << binary_search(array, 3) << std::endl;
     std::cout << binary_search(array, 4) << std::endl;
     std::cout << binary_search(array, 5) << std::endl;
     std::cout << binary_search(array, 6) << std::endl;
     std::cout << binary_search(array, 7) << std::endl;
     std::cout << binary_search(array, 8) << std::endl;
     std::cout << binary_search(array, 9) << std::endl;
     std::cout << binary_search(array, 10) << std::endl;
     std::cout << binary_search(array, 11) << std::endl;
     std::cout << binary_search(array, 12) << std::endl;
     std::cout << binary_search(array, 0) << std::endl;
     std::cout << binary_search(array, -1) << std::endl;
     return 0;
}