#ifndef UNORDERED_LIST_HPP
#define UNORDERED_LIST_HPP
#include "ordered_list.hpp"
#include "index_set.hpp"

namespace ds{
   
     template<
          typename T,
          typename Allocator
     >
     class unordered_list{
          
          using allocator_t = Allocator;
          using allocator_traits_t = std::allocator_traits<allocator_t>;
     public:
          unordered_list(size_t capacity = _default_capacity) 
               : _buffer(allocator_traits_t::allocate(_allocator, capacity)),
                 _capacity(capacity),
                 _indexes(capacity),
                 _index_set(_utils::index_set::required_words(capacity)) 
          {
          }

          unordered_list(unordered_list &&other) noexcept
               :    _buffer(other._buffer),
                    _capacity(other._capacity),
                    _indexes(std::move(other._indexes)),
                    _index_set(std::move(other._index_set)) 
          {
               other._buffer = nullptr;
               other._capacity = 0; 
          }

          unordered_list &operator =(unordered_list &&other) noexcept{
               if (this != &other){
                    std::swap(_buffer, other._buffer);
                    std::swap(_capacity, other._capacity);
                    std::swap(_indexes, other._indexes);
                    std::swap(_index_set, other._index_set);
                    std::swap(_allocator, other._allocator);  
               }
               return *this;
          }
         
          T &operator[](size_t index){
               if (index >= _capacity)
                    throw std::out_of_range("index out of bounds");

               if (not _index_set.test(index)){
                    _index_set.set(index);
                    _indexes.push_back(index);
                    allocator_traits_t::construct(_allocator, &_buffer[index]);
               }
               return _buffer[index];
          }
          const T &operator[](size_t index) const{
               if (index >= _capacity or not _index_set.test(index))
                    throw std::out_of_range("invalid index access");
               return _buffer[index];
          }

          void reserve(size_t new_capacity){
               if (new_capacity <= _capacity) return;
               T* new_buffer = allocator_traits_t::allocate(_allocator, new_capacity);
               for (const auto index : _indexes)
                    allocator_traits_t::construct(_allocator, new_buffer + index, std::move(_buffer[index]));
               allocator_traits_t::deallocate(_allocator, _buffer, _capacity);
               
               _buffer = new_buffer;
               _capacity = new_capacity;
               _index_set.reserve(_utils::index_set::required_words(_capacity));
               _indexes.reserve(new_capacity);
          }

          void shrink_to_fit() {
               if (_indexes.empty() || _capacity == _indexes.size()) return;
               size_t last_index = *(_indexes.end() - 1) + 1;
               if (last_index == _capacity) return;

               T* new_buffer = allocator_traits_t::allocate(_allocator, last_index);
               for (const auto index : _indexes) {
                    allocator_traits_t::construct(_allocator, new_buffer + index, std::move(_buffer[index]));
                    allocator_traits_t::destroy(_allocator, _buffer + index);
               }
               allocator_traits_t::deallocate(_allocator, _buffer, _capacity);
               _buffer = new_buffer;
               _capacity = last_index;
               _index_set.shrink_to_fit();
               _indexes.shrink_to_fit();
}
          
          size_t size() const {return _indexes.size();}
          size_t capacity() const {return _capacity;}
          bool empty() const {return _indexes.empty();}

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
                    iterator operator +(difference_type n) const {return iterator(_ptr, _it + n); }
                    iterator operator -(difference_type n) const {return iterator(_ptr, _it - n); }
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

          iterator begin() {return empty() ? end() : iterator(_buffer, _indexes.begin());}
          iterator end() {return iterator(_buffer, _indexes.end());}
        

          void clear(){
               for (const auto index : _indexes)
                    allocator_traits_t::destroy(_allocator, _buffer + index);
               allocator_traits_t::deallocate(_allocator, _buffer, _capacity);
               _buffer = nullptr;
               _capacity = 0;
               _indexes.clear();
               _index_set.clear();
          }

          ~unordered_list(){
               clear();
          }

     private:
          
          T* _buffer = nullptr;
          size_t _capacity;
          ds::ordered_list<size_t> _indexes; // used for implementation of iterator
          ds::_utils::index_set _index_set; // this is used to check if an index is already in the list
          allocator_t _allocator;
          constexpr static size_t _default_capacity = 8;

     };
}

#endif