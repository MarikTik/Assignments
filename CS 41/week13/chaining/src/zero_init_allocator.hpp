#ifndef ZERO_INIT_ALLOCATOR_HPP
#define ZERO_INIT_ALLOCATOR_HPP
#include <type_traits>
namespace ds::_utils{
     /// @brief an allocator that initializes the memory to zero
     /// @tparam T 
     /// @note T must be trivially default constructible i.e. T must have a default constructor or no constructor at all
     template<typename T>
     struct zero_init_allocator{
          static_assert(std::is_trivially_default_constructible<T>::value, "T must be trivially default constructible");
          using value_type = T;
          using pointer = value_type *;
          zero_init_allocator() = default;

          pointer allocate(size_t n){
               pointer p = new value_type[n]();
               if (not p) throw std::bad_alloc();
               return p;
          }

          void deallocate(pointer p, size_t n [[maybe_unused]]){
               std::free(p);
          }
     };
}
#endif