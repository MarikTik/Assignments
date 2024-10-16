#ifndef UNORDERED_LIST_HPP
#define UNORDERED_LIST_HPP
#include "ordered_list.hpp"
#include "index_set.hpp"
#include <type_traits>

namespace ds{
     /// @brief Represents an unordered dynamic array structure accessible for modification via indexing
     /// @tparam T The type of the elements to store in the list
     /// @tparam Allocator The type of the allocator to use for memory management
     template<
          typename T,
          typename Allocator
     >
     class unordered_list{
          template<typename> class basic_iterator;

          using allocator_t = Allocator;
          using allocator_traits_t = std::allocator_traits<allocator_t>;
     public:
          using iterator = basic_iterator<T>;
          using const_iterator = basic_iterator<const T>;
          
          /// @brief Default constructor with an initial capacity.
          /// @param capacity The initial capacity of the list.
          unordered_list(size_t capacity = _default_capacity) 
               : _buffer(allocator_traits_t::allocate(_allocator, capacity)),
                 _capacity(capacity),
                 _indexes(capacity),
                 _index_set(_utils::index_set::required_words(capacity)) 
          {
          }

          /// @brief Copy constructor.
          /// @param other The list to copy from.
          unordered_list(unordered_list const &other)
               :    _buffer(allocator_traits_t::allocate(_allocator, other._capacity)),
                    _capacity(other._capacity),
                    _indexes(other._indexes),
                    _index_set(other._index_set)
          {
               for (const auto index : _indexes)
                    allocator_traits_t::construct(_allocator, _buffer + index, other._buffer[index]);
          }

          /// @brief Move constructor.
          /// @param other The list to move from.
          unordered_list(unordered_list &&other) noexcept
               :    _buffer(other._buffer),
                    _capacity(other._capacity),
                    _indexes(std::move(other._indexes)),
                    _index_set(std::move(other._index_set)) 
          {
               other._buffer = nullptr;
               other._capacity = 0; 
          }

          /// @brief Copy assignment operator.
          /// @param other The list to copy from.
          /// @return Reference to the current list.
          unordered_list &operator = (unordered_list const &other){
               if (this != &other){
                    clear();
                    _buffer = allocator_traits_t::allocate(_allocator, other._capacity);
                    _capacity = other._capacity;
                    _indexes = other._indexes;
                    _index_set = other._index_set;
                    for (const auto index : _indexes)
                         allocator_traits_t::construct(_allocator, _buffer + index, other._buffer[index]);
               }
               return *this;
          }
       

          /// @brief Move assignment operator.
          /// @param other The list to move from.
          /// @return Reference to the current list.
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

          /// @brief Returns a reference to the element at the specified index
          /// @param index The index of the element to return
          /// @note If the index is not in the list, it is added to the list
          /// @throw std::out_of_range if the index is out of bounds 
          /// @return a reference to the element at the specified index
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

          /// @brief Returns a const reference to the element at the specified index
          /// @param index The index of the element to return
          /// @throw std::out_of_range if the index is out of bounds or the index is not in the list
          /// @return Const reference to the element at the specified index
          T &at(size_t index){
               if (index >= _capacity or not _index_set.test(index))
                    throw std::out_of_range("invalid index access");
               return _buffer[index];
          }

          /// @brief Returns a reference to the element at the specified index
          /// @param index The index of the element to return
          /// @throw std::out_of_range if the index is out of bounds or the index is not in the list
          /// @return Reference to the element at the specified index
          const T &at(size_t index) const{
               if (index >= _capacity or not _index_set.test(index))
                    throw std::out_of_range("invalid index access");
               return _buffer[index];
          }

          /// @brief Reserves a new capacity for the list
          /// @param new_capacity The new capacity to reserve
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

          /// @brief Checks if the specified index is in the list
          /// @param index The index to check
          /// @return Whether the index is in the list
          bool is_used_at(size_t index) const{
               return _index_set.test(index);
          }

          /// @brief Shrinks the capacity of the list to the number of elements in the list
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
          
          /// @brief Returns the number of initialized elements in the list
          /// @note Initialized elements are elements that have been accessed using the index operator
          size_t size() const {return _indexes.size();}

          /// @brief Returns the capacity of the list
          size_t capacity() const {return _capacity;}

          /// @brief Checks if the list is empty
          bool empty() const {return _indexes.empty();}

          /// @brief returns an iterator to the beginning of the list
          iterator begin() {return empty() ? end() : iterator(_buffer, _indexes.begin());}

          /// @brief returns an iterator to the end of the list
          iterator end() {return iterator(_buffer, _indexes.end());}

          /// @brief returns a const iterator to the beginning of the list
          const_iterator cbegin() const {return empty() ? cend() : const_iterator(_buffer, _indexes.cbegin());}
          /// @brief returns a const iterator to the end of the list
          const_iterator cend() const {return const_iterator(_buffer, _indexes.cend());}

          /// @brief returns a const iterator to the beginning of the list
          /// @note This function is provided for compatibility with the standard library. Use cbegin() instead. 
          const_iterator begin() const { return cbegin(); }

          /// @brief returns a const iterator to the end of the list
          /// @note This function is provided for compatibility with the standard library. Use cend() instead.
          const_iterator end() const { return cend(); }

          /// @brief Clears the list and releases memory
          void clear(){
               for (const auto index : _indexes)
                    allocator_traits_t::destroy(_allocator, _buffer + index);
               allocator_traits_t::deallocate(_allocator, _buffer, _capacity);
               _buffer = nullptr;
               _capacity = 0;
               _indexes.clear();
               _index_set.clear();
          }

          /// @brief Destructor
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
          
          template<typename U>
          class basic_iterator {
          public:
               using iterator_category = std::random_access_iterator_tag;
               using difference_type = std::ptrdiff_t;
               using value_type = U;
               using pointer = value_type*;
               using reference = value_type&;
               using index_iterator = typename std::conditional_t<
                    std::is_const<U>::value,  // Check if U is const
                    typename ordered_list<size_t>::const_iterator,
                    typename ordered_list<size_t>::iterator
               >;
          

               basic_iterator() = default;
               basic_iterator(pointer ptr, index_iterator it) : _ptr(ptr), _it(it) {}

               reference operator*() const { return _ptr[*_it]; }
               pointer operator->() const { return &_ptr[*_it]; }
               basic_iterator& operator++() { ++_it; return *this; }
               basic_iterator operator++(int) { basic_iterator temp = *this; ++(*this); return temp; }
               basic_iterator& operator--() { --_it; return *this; }
               basic_iterator operator--(int) { basic_iterator temp = *this; --(*this); return temp; }
               basic_iterator& operator+=(difference_type n) { _it += n; return *this; }
               basic_iterator& operator-=(difference_type n) { _it -= n; return *this; }
               basic_iterator operator+(difference_type n) const { return basic_iterator(_ptr, _it + n); }
               basic_iterator operator-(difference_type n) const { return basic_iterator(_ptr, _it - n); }
               difference_type operator-(const basic_iterator& other) const { return _it - other._it; }

               bool operator==(const basic_iterator& other) const { return _ptr == other._ptr && _it == other._it; }
               bool operator!=(const basic_iterator& other) const { return !(*this == other); }
               bool operator<(const basic_iterator& other) const { return _ptr + *_it < other._ptr + *other._it; }
               bool operator>(const basic_iterator& other) const { return _ptr + *_it > other._ptr + *other._it; }
               bool operator<=(const basic_iterator& other) const { return _ptr + *_it <= other._ptr + *other._it; }
               bool operator>=(const basic_iterator& other) const { return _ptr + *_it >= other._ptr + *other._it; }

          private:
               pointer _ptr = nullptr;
               index_iterator _it;
          };
     };
}

#endif