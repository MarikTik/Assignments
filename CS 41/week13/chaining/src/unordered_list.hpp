#ifndef UNORDERED_LIST_HPP
#define UNORDERED_LIST_HPP
#include "ordered_list.hpp"
#include "circular_list.hpp"

namespace ds{
     template<typename T>
     class unordered_list{
     public:
          unordered_list() : _buffer(new T[_default_capacity]), _indexes(_default_capacity) {}
          unordered_list(size_t capacity) : _buffer(new T[capacity]), _indexes(capacity) {}
          unordered_list(unordered_list &&other) : _buffer(other._buffer), _indexes(std::move(other._indexes)) {}
          unordered_list &operator =(unordered_list &&other){
               if (this == &other) return *this;
               delete[] _buffer;
               _buffer = other._buffer, _indexes = std::move(other._indexes);
               other._buffer = nullptr;
               return *this;
          }

          T &operator[](size_t index){
               if (index >= capacity())
                    throw std::out_of_range("index out of bounds");

               auto iterator = std::find(_indexes_cache.begin(), _indexes_cache.end(), index);
               if (iterator == _indexes_cache.end()){ 
                    _indexes_cache.insert(index);
                    iterator = std::find(_indexes.begin(), _indexes.end(), index);
                    if (iterator == _indexes.end()) _indexes.push_back(index);
               }
               
               return _buffer[index];
          }

          void reserve(size_t new_capacity){
               if (new_capacity <= this->capacity) return;
               T* new_buffer = new T[new_capacity];
               for (const auto index : _indexes)
                    new_buffer[index] = std::move(_buffer[index]);
               delete[] this->array;
               _buffer = new_buffer;
               _indexes.reserve(new_capacity);
          }

          inline size_t capacity() const{
               return _indexes.capacity();
          }

          class iterator{
               using iterator_category = std::random_access_iterator_tag;
               using difference_type = std::ptrdiff_t;
               using value_type = T;
               using pointer = value_type *;
               using reference = value_type &;

               using index_iterator = typename ordered_list<size_t>::iterator;
               public:
                    iterator() = default;
                    iterator(T* ptr, index_iterator it) : _ptr(ptr), _it(it) {}
                    reference operator * () const {return _ptr[*_it];}
                    pointer operator -> () const {return &_ptr[*_it];}
                    iterator &operator ++() {_it++; return *this;}
                    iterator operator ++(int) {iterator temp = *this; ++(*this); return temp;}
                    iterator &operator --() {_it--; return *this;}
                    iterator operator --(int) {iterator temp = *this; --(*this); return temp;}
                    iterator &operator +=(difference_type n) {_it += n; return *this;}
                    iterator &operator -=(difference_type n) {_it -= n; return *this;}
                    iterator operator +(difference_type n) const {return iterator(_ptr + *_it + n, _it + n);} // error here
                    iterator operator -(difference_type n) const {return iterator(_ptr + *_it - n, _it - n);} // end here 
                    bool operator ==(const iterator &other) const {return _ptr == other._ptr and _it == other._it;}
                    bool operator !=(const iterator &other) const {return not (*this == other);}
                    bool operator <(const iterator &other) const {return _ptr + *_it < other._ptr + *other._it;}
                    bool operator >(const iterator &other) const {return _ptr + *_it > other._ptr + *other._it;}
                    bool operator <=(const iterator &other) const {return _ptr + *_it <= other._ptr + *other._it;}
                    bool operator >=(const iterator &other) const {return _ptr + *_it >= other._ptr + *other._it;}
                    difference_type operator -(const iterator &other) const {return _ptr + *_it - other._ptr + *other._it;}
               private:
                    T * _ptr = nullptr; index_iterator _it = 0;
          };   
          iterator begin() {return iterator(_buffer, _indexes.begin());}
          iterator end() {return iterator(_buffer, _indexes.end());}
     private:
          ordered_list<size_t> _indexes;
          circular_list<size_t> _indexes_cache{_default_cache_capacity};
          T *_buffer = nullptr;

          constexpr static size_t _default_capacity = 8;
          constexpr static size_t _default_cache_capacity = 4;
     };
}

#endif