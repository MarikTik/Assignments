#include <array>
#include <iostream>

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

template<typename T, size_t N>
index_t index_of(const std::array<T, N> &array, T value){
     for (index_t i = 0; i < N; i++)
          if (array[i] == value)
               return i;
     return -1;
}

//sample program
int main(){
     std::array<int, 5> array = {1, 2, 3, 4, 5};
     std::cout << index_of(array, 3) << std::endl;
     std::cout << index_of(array, 6) << std::endl;
     return 0;
}