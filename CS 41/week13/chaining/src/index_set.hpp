#ifndef INDEX_SET_HPP
#define INDEX_SET_HPP
#include <cstddef>
#include <limits>

#include "buffer.hpp"
#include "zero_init_allocator.hpp"
namespace ds::_utils{
     using allocator = zero_init_allocator<size_t>;
     //size_t popcount(size_t x);
   

     class index_set : public ds::_utils::buffer<size_t, allocator>{
     public:
          using ds::_utils::buffer<size_t, allocator>::buffer;
          using ds::_utils::buffer<size_t, allocator>::operator =;

          void set(size_t index){
               size_t word_index = index / word_size();
               size_t bit_index = index % word_size();
               
               if (word_index >= this->capacity()) throw std::out_of_range("index out of bounds");
               this->_buffer[word_index] |= one << bit_index;
          }
          void reset(size_t index){
               size_t word_index = index / word_size();
               size_t bit_index = index % word_size();

               if (word_index >= this->capacity()) throw std::out_of_range("index out of bounds");
               this->_buffer[word_index] &= ~(one << bit_index);
          }
          bool test(size_t index) const{
               size_t word_index = index / word_size();
               size_t bit_index = index % word_size();
               if (word_index >= this->capacity()) return false;
               return this->_buffer[word_index] & (one << bit_index);
          }
          bool operator[](size_t index) const{
               return test(index);
          }

        
          /// @brief returns the number of bits set to true in the index set
          /// @return size_t
          size_t size() const{
               size_t count = 0;
               for (size_t i = 0; i < this->capacity(); i++)
                    count += popcount(this->_buffer[i]);
               return count;
          };

          constexpr static size_t word_size(){
               return std::numeric_limits<size_t>::digits;
          };
     private:
          static size_t _portable_popcount(size_t x) {
               size_t count = 0;
               while (x) {
                    x &= (x - 1);
                    count++;
               }
               return count;
          }
               
          static size_t popcount(size_t x) {
               #if defined(__GNUC__) || defined(__clang__)
                    return static_cast<size_t>(__builtin_popcountll(x));
               #elif defined(_MSC_VER)
               #include <intrin.h>
                    return __popcnt64(x);  
               #else
                    return _portable_popcount(x);
               #endif
          }
          constexpr static size_t one = static_cast<size_t>(1); 
     };
     
     

}


#endif