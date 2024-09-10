#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP
#include <cstdint>

template <typename T>
class dynamic_array{
     public:
          dynamic_array(size_t capacity)
               : _array(new T[capacity]), _capacity(capacity), _size(0)
          {               
          }

          void push_back(T &&value){
               if (_size == _capacity) reserve(size_t(_capacity * 1.5));
               _array[_size++] = std::forward<T>(value);
          }

          void reserve(size_t capacity){
               if (capacity > _capacity) {
                    T* new_array = new T[capacity];   
                    for (size_t i = 0; i < _size; ++i) {
                         new_array[i] = std::move(_array[i]);   
                    }
                    delete[] _array;   
                    _array = new_array;   
                    _capacity = capacity;   
               }
          }
          class iterator {
          public:
               iterator(T* ptr) : _ptr(ptr) {}

               T& operator*() const { 
                    return *_ptr;
               }
               iterator& operator++() {
                   ++_ptr;
                   return *this;
               }
               bool operator==(const iterator& other) const {
                    return _ptr == other._ptr;
               }
               bool operator!=(const iterator& other) const {
                    return _ptr != other._ptr; 
               }

          private:
               T* _ptr;  
          };

           
          iterator begin() const { return iterator(_array); }
          iterator end() const { return iterator(_array + _size); }

          ~dynamic_array(){
               delete[] _array;
          }
          
     private:
          T *_array;
          size_t _capacity;
          size_t _size;

};


#endif