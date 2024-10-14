#ifndef INDEX_SET_HPP
#define INDEX_SET_HPP
#include <cstddef>
#include <limits>
#include "zero_init_allocator.hpp"

namespace ds::_utils{
     

     class index_set{
     public:
          index_set(size_t capacity = 4) 
               : _buffer(new size_t[capacity]()), 
                 _capacity(capacity)
          {
          }
          index_set(index_set &&other) noexcept
               : _buffer(other._buffer),
                 _capacity(other._capacity)
          {
               other._buffer = nullptr;
               other._capacity = 0;
          }
          index_set &operator=(index_set &&other) noexcept{
               if (this == &other) return *this;
               delete[] _buffer;
               _buffer = other._buffer;
               _capacity = other._capacity;
               other._buffer = nullptr;
               other._capacity = 0;
               return *this;
          }
          void set(size_t index){
               auto [word_index, bit_index] = word_and_bit_index(index);
               if (word_index >= this->capacity()) throw std::out_of_range("index out of bounds");
               this->_buffer[word_index] |= one << bit_index;
          }
          void reset(size_t index){
               auto [word_index, bit_index] = word_and_bit_index(index);
               if (word_index >= this->capacity()) throw std::out_of_range("index out of bounds");
               this->_buffer[word_index] &= ~(one << bit_index);
          }
          bool test(size_t index) const{
               auto [word_index, bit_index] = word_and_bit_index(index);
               if (word_index >= _capacity) return false;
               return this->_buffer[word_index] & (one << bit_index);
          }

          bool operator[](size_t index) const{
               return test(index);
          }
          void reserve(size_t new_capacity){
               if (new_capacity <= _capacity) return;
               size_t *new_buffer = new size_t[new_capacity]();
               std::copy(_buffer, _buffer + _capacity, new_buffer);
               delete[] _buffer;
               _buffer = new_buffer;
               _capacity = new_capacity;
          }
          void shrink_to_fit(){
               size_t new_capacity = used_capacity();
               if (new_capacity == _capacity) return;
               size_t *new_buffer = new size_t[new_capacity]();
               std::copy(_buffer, _buffer + new_capacity, new_buffer);
               delete[] _buffer;
               _buffer = new_buffer;
               _capacity = new_capacity;
          }
          /// @brief returns the number of bits set to true in the index set
          size_t count() const{
               size_t count = 0;
               for (size_t i = 0; i <= used_capacity(); i++)
                    count += popcount(_buffer[i]);
               return count;
          };

          /// @brief returns the number words in the index set
          size_t capacity() const{
               return _capacity;
          }

          constexpr static size_t word_bitsize(){
               return std::numeric_limits<size_t>::digits;
          };

          constexpr static size_t required_words(size_t capacity) {
               return (capacity + index_set::word_bitsize() - 1) / index_set::word_bitsize();
          }

          void clear(){
               delete[] _buffer;
               _buffer = nullptr;
               _capacity = 0;
          }
          ~index_set(){
               delete[] _buffer;
          }
     private:
          size_t * _buffer = nullptr;
          size_t _capacity = 0;


          size_t used_capacity() const {
               for (size_t i = _capacity; i > 0; --i) 
                    if (_buffer[i - 1] != 0) 
                         return i;
               return 0;
          }
          static std::pair<size_t, size_t> word_and_bit_index(size_t index){
               return {index / word_bitsize(), index % word_bitsize()};
          }
          static size_t popcount(size_t x) {
#if defined(__GNUC__) || defined(__clang__)
                    return static_cast<size_t>(__builtin_popcountll(x));
#elif defined(_MSC_VER)
                    #include <intrin.h>
                    return __popcnt64(x);  
#else
                    size_t count = 0;
                    while (x) {
                         x &= (x - 1);
                         count++;
                    }
                    return count;
#endif
          }
          constexpr static size_t one = static_cast<size_t>(1); 
     };
     
     

}


#endif