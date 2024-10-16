#include <utility>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <iostream>

namespace ds{
     template<typename T>
     struct dl_node{
          template<typename... Args>
          dl_node(Args&&... args) : data(std::forward<Args>(args)...)
          {   
          }
          dl_node(dl_node &&other) : previous{other.previous}, next{other.next}, data{std::move(other.data)}
          {
               other.previous = other.next = nullptr;
          }
          void attach_next(dl_node<T> *next_node){
               if (not next_node) return;
               next_node->previous = this;
               this->next = next_node;
          }
          void attach_previous(dl_node<T> *previous_node){
               if (not previous_node) return;
               previous_node->next = this;
               this->previous = previous_node;
          }
          dl_node<T> *previous = nullptr;
          dl_node<T> *next = nullptr;
          T data;
     };

     template<
          typename T,
          typename Allocator = std::allocator<dl_node<T>>
     >
     class linked_list{
          using allocator_t = Allocator;
          using node_t = dl_node<T>;
          using node_allocator_t = typename std::allocator_traits<Allocator>::template rebind_alloc<node_t>;
          using node_allocator_traits_t = std::allocator_traits<node_allocator_t>;

          template<typename> class basic_iterator;
     public:
          using iterator = basic_iterator<T>;
          using const_iterator = basic_iterator<const T>;
          /// @brief Constructs an empty linked list.
          linked_list() = default;

          /// @brief Constructs a linked list as a copy of another list.
          /// @param other The linked list to copy from.
          linked_list(const linked_list &other) 
               : _allocator(other._allocator),
                 _node_allocator(other._node_allocator)
          {
               insert_back(other.begin(), other.end());
          }

          /// @brief Assigns the contents of another linked list to this one.
          /// @param other The linked list to copy from.
          /// @return Reference to the current object.
          linked_list &operator =(const linked_list &other){
               if (this != &other)
               {
                    clear();
                    _allocator = other._allocator;
                    _node_allocator = other._node_allocator;
                    insert_back(other.begin(), other.end());
               }
               return *this;
          }

          /// @brief Constructs a linked list by moving the contents of another list.
          /// @param other The linked list to move from.
          linked_list(linked_list &&other) noexcept
               : _head(other._head), _tail(other._tail),
               _allocator(std::move(other._allocator)),
               _node_allocator(std::move(other._node_allocator))
          {
               other._head = other._tail = nullptr;
          }

          /// @brief Moves the contents of another linked list into this one.
          /// @param other The linked list to move from.
          /// @return Reference to the current object.
          linked_list &operator = (linked_list &&other) noexcept{
               if (this != &other) {
                    std::swap(_head, other._head);
                    std::swap(_tail, other._tail);
                    std::swap(_allocator, other._allocator);
                    std::swap(_node_allocator, other._node_allocator);
               }
               return *this;
          }

          /// @brief Inserts a new element at the end of the list.
          /// @tparam Args The types of the arguments to construct the element.
          /// @param args The arguments to forward to the element's constructor.
          template<typename... Args>
          void emplace_back(Args &&...args){
               auto *node = _node_allocator.allocate(1);
               node_allocator_traits_t::construct(_node_allocator, node, std::forward<Args>(args)...);

               if (not _head) {
                    _head = _tail = node;
               }
               else{
                    _tail->attach_next(node);
                    _tail = node;
               }
          }

          /// @brief Inserts a new element at the beginning of the list.
          /// @tparam Args The types of the arguments to construct the element.
          /// @param args The arguments to forward to the element's constructor.
          template<typename... Args>
          void emplace_front(Args &&...args){
               auto *node = _node_allocator.allocate(1);
               node_allocator_traits_t::construct(_node_allocator, node, std::forward<Args>(args)...);

               if (not _head){
                    _head = _tail = node;
               }
               else{
                    _head->attach_previous(node);
                    _head = node;
               }
          }

          /// @brief Inserts a new element at the end of the list.
          /// @tparam Arg The type of the value to be inserted.
          /// @param value The value to be inserted.
          template<typename Arg>
          void push_back(Arg &&value){
               emplace_back(std::forward<Arg>(value));
          }   

          /// @brief Inserts a new element at the beginning of the list.
          /// @tparam Arg The type of the value to be inserted.
          /// @param value The value to be inserted.
          template<typename Arg>
          void push_front(Arg &&value){
               emplace_front(std::forward<Arg>(value));
          }

          /// @brief Inserts a range of elements into the back of the list.
          /// @tparam InputIt The type of the input iterator.
          /// @param begin Iterator to the beginning of the range.
          /// @param end Iterator to the end of the range.
          template<typename InputIt>
          void insert_front(InputIt begin, InputIt end){
               for (auto it = begin; it != end; ++it)
                    push_back(*it);
          }

          /// @brief Inserts a range of elements into the front of the list.
          /// @tparam InputIt The type of the input iterator.
          /// @param begin Iterator to the beginning of the range.
          /// @param end Iterator to the end of the range.
          template<typename InputIt>
          void insert_back(InputIt begin, InputIt end){
               for (auto it = begin; it != end; ++it)
                    push_front(*it);
          }
          
          /// @brief Returns the number of elements in the list.
          /// @note This function has linear complexity.
          /// @return The size of the list.
          size_t size() const {
               size_t count = 0;
               for (auto* ptr = _head; ptr != nullptr; ptr = ptr->next) ++count;
               return count;
          }

          /// @brief Checks if the list is empty.
          /// @return True if the list is empty, false otherwise. 
          bool empty() const{
               return not _head;
          }

          /// @brief Clears the contents of the list.
          void clear(){
               auto* ptr = _head;
               _head = _tail = nullptr;

               while (ptr) {
                   auto* next = ptr->next;
                   node_allocator_traits_t::destroy(_node_allocator, ptr);
                   _node_allocator.deallocate(ptr, 1);
                   ptr = next;
               }
          }

          /// @brief Erases an element from the list by the specified iterator.
          /// @param it The iterator pointing to the element to erase.
          /// @return Iterator to the next element in the list.
          iterator erase(iterator it) {
               if (it == end()) return end();

               dl_node<T>* node = it._ptr;
               dl_node<T>* next = node->next;
               dl_node<T>* previous = node->previous;

               if (previous) previous->next = next;
               else _head = next;

               if (next) next->previous = previous;
               else _tail = previous;

               node_allocator_traits_t::destroy(_node_allocator, node);
               _node_allocator.deallocate(node, 1);

               return iterator(next);
          }    

          /// @brief Removes elements from the specified range that satisfy a predicate.
          /// @tparam Predicate the type of the predicate function.
          /// @param predicate the predicate function.
          /// @param begin the iterator to the beginning of the range.
          /// @param end the iterator to the end of the range.
          /// @return iterator to the next element after the last removed element.
          template<typename Predicate>
          iterator remove_if(Predicate predicate, iterator begin, iterator end){
               auto it = std::find_if(begin, end, predicate);
               return erase(it);
          }    

          /// @brief Removes elementsfrom the list that satisfy a predicate.
          /// @tparam Predicate the type of the predicate function.
          /// @param predicate the predicate function.
          /// @return the iterator to the next element after the last removed element.
          template<typename Predicate>
          iterator remove_if(Predicate predicate){
               return remove_if(predicate, begin(), end());
          }

          /// @brief Returns an iterator to the beginning of the list.
          iterator begin() { return iterator(_head); }

          /// @brief Returns an iterator to the end of the list.
          iterator end() { return iterator(nullptr); }

          /// @brief Returns a const iterator to the beginning of the list.
          const_iterator cbegin() const { return const_iterator(_head); }

          /// @brief Returns a const iterator to the end of the list. 
          const_iterator cend() const { return const_iterator(nullptr); }

          /// @brief Returns a const iterator to the beginning of the list.
          /// @note This function is provided for compatibility with the standard library. Use cbegin() instead.
          const_iterator begin() const { return const_iterator(_head); }

          /// @brief Returns a const iterator to the end of the list.
          /// @note This function is provided for compatibility with the standard library. Use cend() instead.
          const_iterator end() const { return const_iterator(nullptr); }

          /// @brief Returns a reference to the first element in the list.
          /// @return T&
          T& front() const { return _head->data; }
          
          /// @brief Returns a const reference to the first element in the list.
          //const T& front() const { return _head->data; }

          /// @brief Returns a reference to the last element in the list.
          /// @return 
          T& back() const { return _tail->data; }

          /// @brief Returns a const reference to the last element in the list.
          /// @return
          //const T& back() const { return _tail->data; }

          /// @brief Destructor that clears the contents of the list.
          ~linked_list(){ 
               clear();
          }

     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
          allocator_t _allocator;
          node_allocator_t _node_allocator;

          template<typename U>
          class basic_iterator {
          public:
               using iterator_category = std::bidirectional_iterator_tag;
               using difference_type = std::ptrdiff_t;
               using value_type = U;
               using pointer = value_type*;
               using reference = value_type&;


               basic_iterator() = default;
               explicit basic_iterator( dl_node<T> *ptr) : _ptr(ptr) {}
               reference operator*() const { return _ptr->data; }
               pointer operator->() const { return &(_ptr->data); }
               basic_iterator& operator++() {_ptr = _ptr->next; return *this; }
               basic_iterator operator++(int) {basic_iterator tmp = *this; ++(*this); return tmp; }
               basic_iterator& operator--() {_ptr = _ptr->previous; return *this; }
               basic_iterator operator--(int) {basic_iterator tmp = *this; --(*this); return tmp; }
               bool operator==(const basic_iterator& other) const { return _ptr == other._ptr; }
               bool operator!=(const basic_iterator& other) const { return _ptr != other._ptr; }

          private:
               dl_node<T> *_ptr = nullptr;    
               friend class linked_list;
          };
     };

     namespace _utils{
          class index_set{
          public:
               index_set(size_t capacity = 4) 
                    : _buffer(new size_t[capacity]()), 
                      _capacity(capacity)
               {
               }
               index_set(const index_set &other)
                    : _buffer(new size_t[other._capacity]()),
                      _capacity(other._capacity)
               {
                    std::copy(other._buffer, other._buffer + other._capacity, _buffer);
               }
               index_set &operator=(const index_set &other){
                    if (this != &other) {
                         delete[] _buffer;
                         _buffer = new size_t[other._capacity]();
                         _capacity = other._capacity;
                         std::copy(other._buffer, other._buffer + other._capacity, _buffer);
                    }
                    return *this;
               }
               index_set(index_set &&other) noexcept
                    : _buffer(other._buffer),
                      _capacity(other._capacity)
               {
                    other._buffer = nullptr;
                    other._capacity = 0;
               }
               index_set &operator=(index_set &&other) noexcept{
                    if (this != &other){
                         delete[] _buffer;
                         _buffer = other._buffer;
                         _capacity = other._capacity;
                         other._buffer = nullptr;
                         other._capacity = 0;
                    };
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
               constexpr static size_t one = static_cast<size_t>(1); 

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
          };
     }

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

     template<
          typename Key,
          typename Value,
          typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<std::pair<const Key, Value> >
     >
     class hash_table{
               using item_t = std::pair<const Key, Value>;
               using chain_t = linked_list<item_t, Allocator>;
               using chain_allocator_t = typename Allocator::template rebind<chain_t>::other;
               using table_t = unordered_list<chain_t, chain_allocator_t>;

               template<typename> class basic_iterator;
          public:
               using iterator = basic_iterator<item_t>;
               using const_iterator = basic_iterator<const item_t>;

               /// @brief Default constructor.
               hash_table() = default;

               /// @brief Constructs a hash table with the specified capacity.
               /// @param capacity The initial capacity of the hash table.
               hash_table(size_t capacity) 
                    : _table(capacity)
               {
               }

               /// @brief Copy constructor.
               /// @param other The hash table to copy from.
               hash_table(const hash_table &other) 
                    : _table(other._table)
               {
               }

               /// @brief Move constructor.
               /// @param other The hash table to move from.
               hash_table(hash_table &&other) noexcept 
                    : _table(std::move(other._table))
               {
               }

               /// @brief Constructs a hash table with the specified items.
               /// @param items The list of items to insert into the hash table.
               hash_table(std::initializer_list<item_t> items) 
                    : _table(items.size() * 2)
               {
                    for (auto &&item : items) insert(item);
               }

               /// @brief Copy assignment operator.
               /// @param other The hash table to copy from.
               /// @return Reference to the current hash table.
               hash_table &operator =(const hash_table &other){
                    if (this != &other) _table = other._table;
                    return *this;
               }

               /// @brief Move assignment operator.
               /// @param other The hash table to move from.
               /// @return Reference to the current hash table.
               hash_table &operator =(hash_table &&other) noexcept{
                    if (this != &other) _table = std::move(other._table);
                    return *this;
               }

               /// @brief Construct an item directly in the hash table at the specified key
               /// @tparam Args The types of the arguments to construct the item.
               /// @param key The key to construct the item at.
               /// @param args The arguments to forward to the item's constructor.
               template<typename... Args>
               void emplace(const Key &key, Args &&...args) {
                    auto_rehash();
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];

                    for (auto &kvp : chain) 
                         if (KeyEqual{}(kvp.first, key))  
                              return;

                    chain.emplace_back(
                         std::piecewise_construct,
                         std::forward_as_tuple(key),
                         std::forward_as_tuple(std::forward<Args>(args)...)
                    );
               }

               /// @brief Moves a new key-value pair into the hash table.
               /// @param key_value_pair The key-value pair to insert.
               void insert(item_t &&key_value_pair){
                    auto_rehash();
                    auto &key = key_value_pair.first;
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];

                    auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });

                    if (it != chain.end()) return;
                    else chain.emplace_back(std::move(key_value_pair));
               }

               /// @brief Inserts a new key-value pair into the hash table.
               /// @param key_value_pair The key-value pair to insert.
               void insert(const item_t &key_value_pair){
                    insert(item_t{key_value_pair});
               }

               /// @brief Inserts a new key-value pair into the hash table.
               /// @param key The key to insert.
               /// @param value The value to insert.
               void insert(const Key &key, const Value &value){
                    insert(item_t{key, value});
               }

               /// @brief Inserts a range of key-value pairs into the hash table.
               /// @tparam InputIt An input iterator of any container.
               /// @param begin The iterator to the beginning of the range.
               /// @param end The iterator to the end of the range.
               template<typename InputIt>
               void insert(InputIt begin, InputIt end){
                    for (auto it = begin; it != end; ++it) insert(*it);
               }

               /// @brief Inserts a range of key-value pairs into the hash table.
               /// @tparam Range The type of the range.
               /// @param range The range to insert.
               template<typename Range>
               void insert(const Range &range){
                    insert(std::begin(range), std::end(range));
               }

               /// @brief Inserts a new key-value pair into the hash table, if it already exists, updates the value.
               /// @param key The key to insert.
               /// @param value The value to insert.
               void insert_or_assign(const Key &key, const Value &value){
                    auto_rehash();
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];

                    auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });

                    if (it != chain.end()) it->second = value;
                    else insert(key, value);
               }

               /// @brief Returns a const value associated with the specified key.
               /// @param key The key to search for.
               /// @throw std::out_of_range if the key is not found.
               /// @return The value associated with the key.
               const Value &at(const Key &key) const{
                    size_t index = Hash{}(key) % _table.capacity();
                    const chain_t &chain = _table.at(index);

                    auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });

                    if (it != chain.end()) return it->second;
                    throw std::out_of_range("key not found");
               }

               /// @brief Returns a value reference associated with the specified key.
               /// @param key The key to search for.
               /// @throw std::out_of_range if the key is not found.
               /// @return The value reference associated with the key.
               Value &at(const Key &key){
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table.at(index);

                    auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });
                    if (it != chain.end()) return it->second;
                    throw std::out_of_range("key not found");
               }

               /// @brief Returns a value reference associated with the specified key, if it does not exist, default constructs a new value.
               /// @param key The key to search for.
               /// @return The value reference associated with the key.
               Value& operator[](const Key& key) {
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t& chain = _table[index];

                    auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });
                    if (it != chain.end()) return it->second;

                    chain.emplace_back(
                         std::piecewise_construct,
                         std::forward_as_tuple(key),
                         std::forward_as_tuple()
                    );
                    return chain.back().second;
               }

               /// @brief Erases the key-value pair associated with the specified key.
               /// @param key The key to erase.
               void erase(const Key &key){
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];
                    chain.remove_if([&key](const auto &key_value_pair){
                         return KeyEqual{}(key_value_pair.first, key);
                    });
               }

               /// @brief Returns the load factor of the hash table.
               float load_factor() const{
                    return static_cast<float>(_table.size()) / static_cast<float>(_table.capacity());
               }

               /// @brief Seeks the specified key in the hash table.
               /// @param key The key to search for.
               /// @return const_iterator to the key-value pair if it was found, cend() otherwise.
               const_iterator find(const Key &key) const{
                    size_t index = Hash{}(key) % _table.capacity();

                    if (not _table.is_used_at(index)) return cend();

                    const chain_t &chain = _table.at(index);

                    const auto it = std::find_if(chain.cbegin(), chain.cend(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });

                    return const_iterator{_table.cbegin(), _table.cend(), it};
               }

               /// @brief Seeks the specified key in the hash table.
               /// @param key The key to search for.
               /// @return iterator to the key-value pair if it was found, end() otherwise.
               iterator find(const Key &key){
                    size_t index = Hash{}(key) % _table.capacity();
                    if (not _table.is_used_at(index)) return end();

                    chain_t &chain = _table.at(index);

                    auto it = std::find_if(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });

                    return iterator{_table.begin(), _table.end(), it};
               }
               
               /// @brief Checks if the specified key is in the hash table.
               /// @param key The key to search for.
               /// @return True if the key is in the hash table, false otherwise.
               bool contains(const Key &key) const{
                    auto index = Hash{}(key) % _table.capacity();

                    if (not _table.is_used_at(index)) return false;

                    const auto &chain = _table.at(index);

                    return std::any_of(chain.begin(), chain.end(), [&key](const auto &kvp){
                         return KeyEqual{}(kvp.first, key);
                    });
               }
               
               /// @brief Returns the current capacity of the hash table.
               size_t capacity() const{
                    return _table.capacity();
               }
               
               /// @brief Returns whether the hash table is empty.
               /// @note This function has linear complexity or potentially quadratic.
               bool empty() const{
                    return not size();
               }
               
               /// @brief Returns the number of elements in the hash table.
               /// @note This function has linear complexity or potentially quadratic.
               size_t size() const{
                    size_t count = 0;
                    for (const auto &chain : _table) count += chain.size();
                    return count;     
               }

               /// @brief Returns an iterator to the beginning of the hash table.
               iterator begin() { return iterator{_table.begin(), _table.end()}; }
               
               /// @brief Returns an iterator to the end of the hash table.
               iterator end() { return iterator{_table.end(), _table.end()}; }

               /// @brief Returns a const iterator to the beginning of the hash table.
               const_iterator cbegin() const { return const_iterator{_table.begin(), _table.end()}; }

               /// @brief Returns a const iterator to the end of the hash table.
               const_iterator cend() const { return const_iterator{_table.end(), _table.end()}; }

               /// @brief Returns a const iterator to the beginning of the hash table.
               /// @note This function is provided for compatibility with the standard library. Use cbegin() instead.
               const_iterator begin() const { return cbegin(); }

               /// @brief Returns a const iterator to the end of the hash table.
               /// @note This function is provided for compatibility with the standard library. Use cend() instead.
               const_iterator end() const { return cend(); }

               
               void rehash(size_t new_capacity){
                    if (new_capacity <= _table.capacity()) return;
                    unordered_list<chain_t, chain_allocator_t> new_table(new_capacity);

                    for (auto &chain : _table){
                         for (auto &kvp : chain) {
                              size_t index = Hash{}(kvp.first) % new_capacity;
                              new_table[index].emplace_back(std::move(kvp));
                         }
                    }
                    _table = std::move(new_table);
               }

               /// @brief Reserves the specified capacity for the hash table.
               /// @param new_capacity The new capacity to reserve. 
               void reserve(size_t new_capacity){
                    rehash(new_capacity);
               }

               /// @brief Sets the maximum load factor of the hash table.
               void max_load_factor(float factor){
                    _max_load_factor = factor;
               }

               /// @brief Clears the hash table and releases memory.
               void clear(){
                    _table.clear();
               }
          private:
               unordered_list<chain_t, chain_allocator_t> _table;
               float _max_load_factor = 0.75f;

               void auto_rehash(){
                    if (load_factor() > _max_load_factor) rehash(_table.capacity() * 2);
               }

               template<typename U>
               class basic_iterator{
                    public:
                         using iterator_category = std::forward_iterator_tag;
                         using difference_type = std::ptrdiff_t;
                         using value_type = U;
                         using pointer = value_type*;
                         using reference = value_type&;

                         using element_iterator_t = std::conditional_t<
                              std::is_const<U>::value,
                              typename chain_t::const_iterator,
                              typename chain_t::iterator
                         >;
                         using chain_iterator_t = std::conditional_t<
                              std::is_const<U>::value,
                              typename table_t::const_iterator,
                              typename table_t::iterator
                         >;

                         basic_iterator(chain_iterator_t chain_it, chain_iterator_t chain_end)
                              : _chain_it(chain_it),
                                _chain_end(chain_end)
                         {
                              if (_chain_it != _chain_end) {
                                   _element_it = _chain_it->begin();
                                   advance();
                              }
                         }
                         basic_iterator (chain_iterator_t chain_it, chain_iterator_t chain_end, element_iterator_t element_it)
                              : _chain_it(chain_it),
                                _chain_end(chain_end),
                                _element_it(element_it)
                         {
                         }
                         reference operator*() const {
                              return *_element_it;
                         }
                         pointer operator->() const {
                              return &(*_element_it);
                         }
                         basic_iterator &operator ++(){
                              ++_element_it;
                              if (_element_it == _chain_it->end()) {
                                   ++_chain_it;
                                   advance();
                              }
                              return *this;
                         }
                         basic_iterator operator++(int) {
                              basic_iterator temp = *this;
                              ++(*this);
                              return temp;
                         }
                         bool operator == (const basic_iterator &other) const{
                              return _chain_it == other._chain_it and _element_it == other._element_it;
                         }
                         bool operator != (const basic_iterator &other) const{
                              return not (*this == other);
                         }
                    private:
                         chain_iterator_t _chain_it;
                         chain_iterator_t _chain_end;
                         element_iterator_t _element_it;

                         void advance(){
                              while (_chain_it != _chain_end) {
                                   _element_it = _chain_it->begin();  
                                   if (_element_it != _chain_it->end()) break;  
                                   ++_chain_it;  
                              }
                         }
               };
     };
}

int main(){
     ds::hash_table<std::string, int> table {
          {"one", 1},
          {"two", 2},
          {"three", 3},
          {"four", 4},
          {"five", 5}
     };

     table.insert({"six", 6});
     table.emplace("seven", 7);
     table.insert_or_assign("eight", 8);
     table.erase("three");
     for (const auto &kvp : table){
          std::cout << kvp.first << " : " << kvp.second << std::endl;
     }

}