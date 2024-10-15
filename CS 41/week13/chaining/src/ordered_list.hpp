#ifndef ORDERED_LIST_HPP
#define ORDERED_LIST_HPP
#include <limits>
 
namespace ds{
     /// @brief list that keeps the elements in the order they were added
     /// @note the list will automatically increase its capacity when the number of elements exceeds the current capacity
     /// @warning retreaval of elements throgugh the [] operator is allowed, however altering the reference in any way
     /// is strongly discouraged and will impact the integrity of the list
     /// @tparam T type of the elements to be stored in the list
     template<
          typename T,
          typename Allocator = std::allocator<T>
     >
     class ordered_list{
          using allocator_t = Allocator;
          using allocator_traits_t = std::allocator_traits<allocator_t>;

          template<typename U> class basic_iterator;

          public:
               using iterator = basic_iterator<T>;
               using const_iterator = basic_iterator<const T>;

               /// @brief Default constructor with an initial capacity.
               ordered_list(size_t capacity = _default_capacity)
                    : _buffer(allocator_traits_t::allocate(_allocator, capacity)),
                      _capacity(capacity)
               {
               }

               /// @brief Copy constructor.
               /// @param other The list to copy from.
               ordered_list(const ordered_list &other)
                    : _buffer(allocator_traits_t::allocate(_allocator, other._capacity)),
                      _capacity(other._capacity),
                      _size(other._size)
               {
                    std::uninitialized_copy(other._buffer, other._buffer + other._size, _buffer);
               }

               /// @brief Copy assignment operator.
               /// @param other The list to copy from.
               /// @return Reference to this list.
               ordered_list &operator =(const ordered_list &other){
                    if (this != &other) {
                         clear();
                         if (_capacity < other._size) reserve(other._size);
                         std::uninitialized_copy(other._buffer, other._buffer + other._size, _buffer);
                         _size = other._size;
                    }
                    return *this;
               }
               /// @brief Move constructor.
               /// @param other The list to move from.
               ordered_list(ordered_list &&other) noexcept
                    : _buffer(other._buffer),
                      _capacity(other._capacity),
                      _size(other._size)
               {
                    other._buffer = nullptr, other._capacity = 0, other._size = 0;
               }

               /// @brief Move assignment operator.
               /// @param other The list to move from.
               /// @return Reference to this list.
               ordered_list &operator =(ordered_list &&other) noexcept{
                    if (this != &other) {
                         std::swap(_buffer, other._buffer);
                         std::swap(_capacity, other._capacity);
                         std::swap(_size, other._size);
                    }
                    return *this;
               }
           

               /// @brief Adds a new element to the list at the end.
               /// @tparam Arg The type of the value to be added.
               /// @param value The value to be added.
               template<typename Arg>
               void push_back(Arg &&value){
                    if (_size == _capacity) reserve(_capacity * 2);
                    allocator_traits_t::construct(_allocator, _buffer + _size++, std::forward<Arg>(value));
               }

               /// @brief Removes the element at the specified iterator.
               /// @param it The iterator pointing to the element to be removed.
               void remove(iterator it) {
                    if (it == end()) return;
                    std::move(it + 1, end(), it);
                    allocator_traits_t::destroy(_allocator, _buffer + --_size);
               }

               /// @brief returns a const reference to element at the specified index
               /// @param index 
               /// @return const T&
               /// @throw std::out_of_range if the index is out of bounds
               const T& operator[](size_t index) const{
                    if (index >= this->_size) throw std::out_of_range("index out of bounds");
                    return _buffer[index];
               }

               /// @brief reserves the specified capacity for the list
               /// @param new_capacity 
               void reserve(size_t new_capacity) {
                    if (new_capacity >= _capacity) reallocate(new_capacity);
               }

               /// @brief Shrinks the capacity to fit the current size.
               void shrink_to_fit() {
                    if (_size < _capacity) reallocate(_size);
               }

               /// @brief Clears the list and releases memory.
               void clear() {
                    destroy_elements();
                    if (_buffer) allocator_traits_t::deallocate(_allocator, _buffer, _capacity);
                    _buffer = nullptr;
                    _capacity = _size = 0;
               }

               /// @brief Returns the current size of the list.
               size_t size() const{
                    return _size;
               }

               /// @brief Returns the current capacity of the list.
               size_t capacity() const{
                    return _capacity;
               }

               /// @brief Returns whether the list is empty.
               bool empty() const{
                    return not _size;
               }
               /// @brief Returns an iterator to the beginning of the list.
               iterator begin() {return iterator(_buffer);}

               /// @brief Returns an iterator to the end of the list.
               iterator end() {return iterator(_buffer + _size);}

               /// @brief Returns a const iterator to the beginning of the list.
               const_iterator cbegin() const {return const_iterator(_buffer);}

               /// @brief Returns a const iterator to the end of the list.
               const_iterator cend() const {return const_iterator(_buffer + _size);}

               /// @brief Destructor to release allocated memory.
               ~ordered_list() { clear(); }
          private:
               T* _buffer = nullptr;
               size_t _capacity, _size = 0;
               allocator_t _allocator;

               static constexpr size_t _default_capacity = 8;
               
               void reallocate(size_t new_capacity) {
                    T* new_buffer = allocator_traits_t::allocate(_allocator, new_capacity);
                    std::uninitialized_move(_buffer, _buffer + _size, new_buffer);
                    destroy_elements();
                    allocator_traits_t::deallocate(_allocator, _buffer, _capacity);
                    _buffer = new_buffer;
                    _capacity = new_capacity;
               }

               void destroy_elements() {
                    for (size_t i = 0; i < _size; ++i) allocator_traits_t::destroy(_allocator, _buffer + i);
               }
               
               template<typename U>
               class basic_iterator{
                    public:
                         using iterator_category = std::random_access_iterator_tag;
                         using difference_type = std::ptrdiff_t;
                         using value_type = U;
                         using pointer = value_type *;
                         using reference = value_type &;
                         basic_iterator() = default;
                         basic_iterator(U* ptr) : _ptr(ptr) {}
                         reference operator * () const {return *_ptr;}
                         pointer operator -> () const {return _ptr;}
                         basic_iterator &operator ++() {++_ptr; return *this;}
                         basic_iterator operator ++(int) {iterator temp = *this; ++(*this); return temp;}
                         basic_iterator &operator --() {--_ptr; return *this;}
                         basic_iterator operator --(int) {iterator temp = *this; --(*this); return temp;}
                         basic_iterator &operator +=(difference_type n) {_ptr += n; return *this;}
                         basic_iterator &operator -=(difference_type n) {_ptr -= n; return *this;}
                         basic_iterator operator +(difference_type n) const {return basic_iterator(_ptr + n);}
                         basic_iterator operator -(difference_type n) const {return basic_iterator(_ptr - n);}
                         difference_type operator -(const basic_iterator &other) const {return _ptr - other._ptr;}
                         bool operator ==(const basic_iterator &other) const {return _ptr == other._ptr;}
                         bool operator !=(const basic_iterator &other) const {return _ptr != other._ptr;}
                         bool operator <(const basic_iterator &other) const {return _ptr < other._ptr;}
                         bool operator > (const basic_iterator &other) const {return _ptr > other._ptr;}
                         bool operator <= (const basic_iterator &other) const {return _ptr <= other._ptr;}
                         bool operator >= (const basic_iterator &other) const {return _ptr >= other._ptr;}
                    private:
                         U* _ptr = nullptr;
               };
     };
}
#endif