#ifndef UNORDERED_LIST_HPP
#define UNORDERED_LIST_HPP
#include "buffer.hpp"
#include "ordered_list.hpp"
#include "index_set.hpp"

namespace ds{
     template<typename T, typename Allocator>
     class unordered_list : public _utils::buffer<T, Allocator>{
     public:
          
          // unordered_list(unordered_list &&other) : _buffer(other._buffer), _indexes(std::move(other._indexes)) {}
          // unordered_list &operator =(unordered_list &&other){
          //      if (this == &other) return *this;
          //      delete[] _buffer;
          //      _buffer = other._buffer, _indexes = std::move(other._indexes);
          //      other._buffer = nullptr;
          //      return *this;
          // }

          using _utils::buffer<T, Allocator>::buffer;
          using _utils::buffer<T, Allocator>::operator =;

          unordered_list() 
               : _utils::buffer<T, Allocator>::buffer(_default_capacity),
                 _indexes(_default_capacity),
                 _index_set(_default_capacity) 
          {
          }
          unordered_list(size_t capacity) 
               : _utils::buffer<T, Allocator>::buffer(capacity),
                 _indexes(capacity),
                 _index_set(capacity) 
          {
          }

          T &operator[](size_t index){
               if (index >= this->_capacity)
                    throw std::out_of_range("index out of bounds");

               if (not _index_set.test(index)){
                    _index_set.set(index);
                    _indexes.push_back(index);
               }
               
               return this->_buffer[index];
          }

          void reserve(size_t new_capacity){
               if (new_capacity <= this->_capacity) return;
               T* new_buffer = this->_allocator.allocate(new_capacity);
               for (const auto index : _indexes)
                    new_buffer[index] = std::move(this->_buffer[index]);
               this->_allocator.deallocate(this->_buffer, this->_capacity);
               this->_buffer = new_buffer;
               this->_capacity = new_capacity;
               _indexes.reserve(new_capacity);
          }

          class iterator{
               public:
                    using iterator_category = std::random_access_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;
                    using pointer = value_type *;
                    using reference = value_type &;
                    using index_iterator = typename ordered_list<size_t>::iterator;
                    
                    iterator() = default;
                    iterator(pointer ptr, index_iterator it) : _ptr(ptr), _it(it) {}

                    reference operator * () const {return _ptr[*_it]; }
                    pointer operator -> () const {return &_ptr[*_it]; }

                    iterator &operator ++() {_it++; return *this; }
                    iterator operator ++(int) {iterator temp = *this; ++(*this); return temp; }
                    iterator &operator --() {_it--; return *this; }
                    iterator operator --(int) {iterator temp = *this; --(*this); return temp; }

                    iterator &operator +=(difference_type n) {_it += n; return *this; }
                    iterator &operator -=(difference_type n) {_it -= n; return *this; }
                    iterator operator +(difference_type n) const {return iterator(_ptr, _it + n); } // error here
                    iterator operator -(difference_type n) const {return iterator(_ptr, _it - n); } // end here 
                    difference_type operator -(const iterator &other) const {return _it - other._it; }

                    bool operator ==(const iterator &other) const {return _ptr == other._ptr and _it == other._it; }
                    bool operator !=(const iterator &other) const {return not (*this == other); }
                    bool operator <(const iterator &other) const {return _ptr + *_it < other._ptr + *other._it; }
                    bool operator >(const iterator &other) const {return _ptr + *_it > other._ptr + *other._it; }
                    bool operator <=(const iterator &other) const {return _ptr + *_it <= other._ptr + *other._it; }
                    bool operator >=(const iterator &other) const {return _ptr + *_it >= other._ptr + *other._it; }
                   
               private:
                    pointer _ptr = nullptr;
                    index_iterator _it;
          };   
          iterator begin() {return iterator(this->_buffer, _indexes.begin());}
          iterator end() {return iterator(this->_buffer, _indexes.end());}
     private:
          ordered_list<size_t> _indexes; // used for implementation of iterator
          ds::_utils::index_set _index_set; // this is used to check if an index is already in the list

          constexpr static size_t _default_capacity = 8;
     };
}

#endif