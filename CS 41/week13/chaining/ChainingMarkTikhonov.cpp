// This implementation features a bigger set of functionality, which will be used in my project4
// for writing the iterators, I consulted the webpage: https://en.cppreference.com/w/cpp/iterator
// and some additional resources, so that my data structures resemble their counterparts from the 
// stl.

#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cassert>
 
namespace ds{
     template<typename T>
     struct dl_node{
          template<typename Arg>
          dl_node(Arg &&val) : data{std::forward<Arg>(val)}
          {
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
          T data;
          dl_node<T> *previous = nullptr;
          dl_node<T> *next = nullptr;
     };

     template<typename T>
     class linked_list{
     public:

          linked_list() = default;
          linked_list(linked_list &&other) : _head(other._head), _tail(other._tail)
          {
               other._head = other._tail = nullptr;
          }
          linked_list &operator = (linked_list &&other){
               _head = other._head, _tail = other._tail;
               other._head = other._tail = nullptr;
          }

          /// @brief inserts a new element at the end of the list
          /// @tparam Arg the type of the value to be inserted
          /// @param value the value to be inserted
          /// @return void
          template<typename Arg>
          void push_back(Arg &&value){
               auto *node = new dl_node<T>(std::forward<Arg>(value));
               if (not _head) {
                    _head = node;
               }
               else if (not _tail) {
                    _tail = node;
                    _tail->attach_previous(_head);
               }
               else{
                    _tail->attach_next(node);
                    _tail = node;
               }
          }   

          /// @brief inserts a new element at the beginning of the list
          /// @tparam Arg the type of the value to be inserted
          /// @param value the value to be inserted
          /// @return void
          template<typename Arg>
          void push_front(Arg &&value){
               auto *node = new dl_node<T>(std::forward<Arg>(value));
               if (not _head){
                    _head = node;
               }
               else if (not _tail){
                    _tail = _head;
                    _head = node;
                    _head->attach_next(_tail);
               }
               else{
                    _head->attach_previous(node);
                    _head = node;
               }
          }

          /// @brief removes the first n elements from an array that satisfy a predicate
          /// @tparam Predicate the type of the predicate to be used
          /// @param predicate the predicate to be used to remove elements
          /// @param n the number of elements to remove, if set to 0, all elements that satisfy the predicate will be removed
          /// @return void
          template<typename Predicate>
          void remove(Predicate predicate, size_t n = 1){
               if (n == 0) n = -1;

               for (auto *ptr = _head; ptr; ptr = ptr->next){
                    if (std::invoke(predicate, ptr->data)){
                         auto *next = ptr->next;
                         if (ptr == _head){
                              delete _head;
                              _head = next;
                         }
                         else{
                              auto *previous = ptr->previous;
                              previous->attach_next(next);
                              delete ptr;
                         }
                         if (--n == 0) return;
                    }
               }
          }

          bool empty() const{
               return _head;
          }

          void clear(){
               for (auto *previous = _head; previous; previous = previous->next) 
                    delete previous;
               _head = _tail = nullptr;
          }

          class iterator {
               public:
                    using iterator_category = std::bidirectional_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;
                    using pointer = value_type *;
                    using reference = value_type &;

                    iterator() = default;
                    iterator(dl_node<T> *head) : current(head) {}

                    reference& operator *() const {return current->data;}
                    iterator& operator ++() {current = current->next; return *this;}
                    iterator operator ++(int) {iterator tmp = *this; current = current->next; return tmp;}
                    iterator& operator --() {current = current->previous; return *this;}
                    iterator operator --(int) {iterator tmp = *this; current = current->previous; return tmp;}
                    bool operator ==(const iterator &other) const {return current == other.current;}
                    bool operator !=(const iterator &other) const {return current != other.current;}

               private:
                   dl_node<T> *current = nullptr;
          };

          iterator begin() const { return iterator(_head); }
          iterator end() const { return iterator(nullptr); }
          ~linked_list(){ clear(); }

     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
     };
}

namespace ds::_utils{
     /// @brief base buffer class that provides a common interface for all types of ordered lists
     /// @tparam T the type of the elements to be stored in the list
     template<typename T>
     class ordered_buffer{
          public:
               ordered_buffer() : _buffer(new T[_default_capacity]), _capacity(_default_capacity) {}
               ordered_buffer(size_t capacity) : _buffer(new T[capacity]), _capacity(capacity) {}
               ordered_buffer(ordered_buffer &&other) : _buffer(other._buffer), _size(other._size), _capacity(other._capacity) {}
               ordered_buffer &operator =(ordered_buffer &&other){
                    if (this == &other) return *this;
                    delete[] _buffer;
                    _buffer = other._buffer, _size = other._size, _capacity = other._capacity;
                    other._buffer = nullptr, other._size = 0, other._capacity = 0;
                    return *this;
               }

               class iterator{
                    public:
                         using iterator_category = std::random_access_iterator_tag;
                         using difference_type = std::ptrdiff_t;
                         using value_type = T;
                         using pointer = value_type *;
                         using reference = value_type &;
                         iterator() = default;
                         iterator(T* ptr) : _ptr(ptr) {}
                         reference operator * () const {return *_ptr;}
                         pointer operator -> () const {return _ptr;}
                         iterator &operator ++() {++_ptr; return *this;}
                         iterator operator ++(int) {iterator temp = *this; ++(*this); return temp;}
                         iterator &operator --() {--_ptr; return *this;}
                         iterator operator --(int) {iterator temp = *this; --(*this); return temp;}
                         iterator &operator +=(difference_type n) {_ptr += n; return *this;}
                         iterator &operator -=(difference_type n) {_ptr -= n; return *this;}
                         iterator operator +(difference_type n) const {return iterator(_ptr + n);}
                         iterator operator -(difference_type n) const {return iterator(_ptr - n);}
                         difference_type operator -(const iterator &other) const {return _ptr - other._ptr;}
                         bool operator ==(const iterator &other) const {return _ptr == other._ptr;}
                         bool operator !=(const iterator &other) const {return _ptr != other._ptr;}
                         bool operator <(const iterator &other) const {return _ptr < other._ptr;}
                         bool operator > (const iterator &other) const {return _ptr > other._ptr;}
                         bool operator <= (const iterator &other) const {return _ptr <= other._ptr;}
                         bool operator >= (const iterator &other) const {return _ptr >= other._ptr;}
                    private:
                         T* _ptr = nullptr;
               };

               /// @brief returns the available capacity of the list
               /// @return size_t
               inline size_t capacity() const {return _capacity;}

               /// @brief returns the currrent number of elements in the list
               /// @return size_t
               inline size_t size() const {return _size;}

               /// @brief reserves a new capacity for the list, if the new capacity is less than the current capacity, the function does nothing
               /// @param new_capacity the new capacity to be reserved
               /// @return void
               void reserve(size_t new_capacity){
                    if (new_capacity <= _capacity) return;
                    T *new_buffer = new T[new_capacity];
                    std::move(_buffer, _buffer + _size, new_buffer);
                    delete[] _buffer;
                    _buffer = new_buffer;
                    _capacity = new_capacity;
               }

               iterator begin() {return iterator(_buffer);}
               iterator end() {return iterator(_buffer + _size);}

               void clear() { delete[] _buffer, _capacity = _size = 0;}
               ~ordered_buffer() { clear(); }
          protected:
               T *_buffer = nullptr;
               size_t _capacity, _size = 0; 
          
          private:
               constexpr static size_t _default_capacity = 8;
     };
}


namespace ds{
     /// @brief list that keeps the elements in the order they were added
     /// @tparam T type of the elements to be stored in the list
     template<typename T>
     class ordered_list : public _utils::ordered_buffer<T>{
          public:
               using _utils::ordered_buffer<T>::ordered_buffer;
               using _utils::ordered_buffer<T>::operator =;

               /// @brief adds a new element to the list at the end
               /// @tparam Arg the type of the element to be added
               /// @param value the value to be added to the list
               /// @return void
               template<typename Arg>
               void push_back(Arg &&value){
                    if (this->_size == this->_capacity) this->reserve(this->_capacity * 2);
                    this->_buffer[this->_size++] = std::forward<T>(value);
               }

               ///@brief removes the first n elements from an array that satisfy a predicate
               ///@tparam Predicate the type of the predicate to be used
               ///@param predicate the predicate to be used to remove elements
               ///@param n the number of elements to remove, if set to 0, all elements that satisfy the predicate will be removed 
               ///@return void
               template<typename Predicate>
               void remove(Predicate predicate, size_t n = 1){
                    if (n == 0) n = this->_size;
               
                    for (size_t i = 0; i < this->_size; i++){
                         if (std::invoke(predicate, this->_buffer[i])){
                              for (size_t j = i; j < this->_size - 1; j++)
                                   this->_buffer[j] = std::move(this->_buffer[j + 1]);
                              this->_size--;
                              if (not --n) break;
                         }
                    }
               }

               /// @brief removes the element pointed by the specified iterator
               /// @param it the iterator pointing to the element to be removed
               /// @return void
               void remove(typename _utils::ordered_buffer<T>::iterator it){
                    if (it == this->end()) return;
                    for (auto next = it + 1; next != this->end(); it++, next++)
                         *it = std::move(*next);
                    this->_size--;
               }
     };
}

namespace ds{
     /// @brief an ordered list that has a fixed capacity and when the list is full, the new elements are added from the beginning of the list
     /// @tparam T type of the elements to be stored in the list
     template<typename T>
     class circular_list : public _utils::ordered_buffer<T>{
          public:
               using _utils::ordered_buffer<T>::ordered_buffer;
               using _utils::ordered_buffer<T>::operator =;

               /// @brief inserts a new value at the end of the list, if the list is full, restarts from the beginning
               /// @tparam Arg the type of the value to be inserted
               /// @param value the value to be inserted
               /// @return void
               template<typename Arg>
               void insert(Arg &&value){
                    if (this->_size < this->_capacity) this->_size ++;
                    this->_buffer[_index] = std::forward<T>(value);
                    this->_index = (_index + 1) % this->_capacity;
               }
          private:
               size_t _index = 0;
     };
}

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
               for (auto it = _indexes.begin(); it != _indexes.end(); it++)
                    new_buffer[*it] = std::move(_buffer[*it]);
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
                    iterator operator +(difference_type n) const {return iterator(_ptr + *_it + n, _it + n);}
                    iterator operator -(difference_type n) const {return iterator(_ptr + *_it - n, _it - n);}
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

namespace ds{
template<
     typename Key,
     typename Value,
     typename Hash = std::hash<Key>
>
class hash_table{
     using item_t = std::pair<Key, Value>;
     using bucket_t = linked_list<item_t>;

     public:
          hash_table()
               : _capacity(_default_bucket_number),
                 _buckets(_default_bucket_number)
          {
          }
          hash_table(size_t capacity)
               : _capacity(capacity),
               _buckets(capacity)
          {
          }

          hash_table(std::initializer_list<item_t> items)
               : _capacity(items.size()),
               _buckets(std::move(items)),
               _size(_capacity)
          {
          }

          template<typename Arg1, typename Arg2>
          void emplace(Arg1&& key, Arg2&& value) {
               if (_size + 1 > _capacity * _load_factor) _rehash(_capacity * 2); 
               size_t bucket_index = _hash(key);
               _buckets[bucket_index].push_back(std::make_pair(std::forward<Arg1>(key), std::forward<Arg2>(value)));
               _size++;
          }

          void remove(const Key &key){
               size_t bucket_index = _hash(key);
               _buckets[bucket_index].remove_if([&key](const auto& item){
                    return item.first == key;
               });
               _size--;
          }

          Value& at(const Key &key){
               size_t bucket_index = _hash(key);
               const bucket_t &bucket = _buckets[bucket_index];
               auto iterator = std::find_if(bucket.begin(), bucket.end(),
                    [&key](const item_t& item){
                         return item.first == key;
                    }
               );
               if (iterator == bucket.end()) throw std::out_of_range("key error: key not found in hash table");
               return (*iterator).second;
          }

          bool contains(const Key &key){
               size_t bucket_index = _hash(key);
               bucket_t &bucket = _buckets[bucket_index];
               auto iterator = std::find_if(bucket.begin(), bucket.end(),
                    [&key](const item_t& item){
                         return item.first == key;
                    }
               );
               return iterator != bucket.end();
          }
          inline size_t size() const{
               return _size;
          }

          class iterator{
               public:
                    using iterator_category = std::bidirectional_iterator_tag;
                    using value_type = item_t;
                    using difference_type = std::ptrdiff_t;
                    using pointer = value_type *;
                    using reference = value_type &;

                    using bucket_iterator_t = typename unordered_list<bucket_t>::iterator;
                    using item_iterator_t = typename linked_list<item_t>::iterator;

                    iterator(
                         bucket_iterator_t bucket_iterator_begin,
                         bucket_iterator_t bucket_iterator_end,
                         item_iterator_t list_iterator
                    )
                        : _bucket_iterator(bucket_iterator_begin),
                         _bucket_iterator_begin(bucket_iterator_begin),
                         _bucket_end_iterator(bucket_iterator_begin),
                         _list_iterator(list_iterator)
                    {
                    }

                    reference operator *() const {
                         return *_list_iterator;
                    }
                    pointer operator ->() const {
                         return &(*_list_iterator);
                    }
                    iterator& operator ++() {
                         if (_list_iterator != _bucket_iterator->end()) {
                              // Move within the current list
                              ++_list_iterator;
                         }               

                         // If we reach the end of the current list, move to the next non-empty bucket
                         while (_list_iterator == _bucket_iterator->end()) {
                         ++_bucket_iterator;
                         if (_bucket_iterator == _bucket_end_iterator) {
                              // If we've reached the end of all buckets, break
                              break;
                         }
                              _list_iterator = _bucket_iterator->begin();  // Move to the start of the new bucket
                         }

                         return *this;
                    }
                    iterator operator ++(int) {
                         iterator temp = *this;
                         ++(*this);
                         return temp;
                    }

                    iterator& operator --() {
                         // Move back within the current list if possible
                         if (_list_iterator != _bucket_iterator->begin()) {
                              --_list_iterator;
                         } 
                         else {
                              // Move back to the previous non-empty bucket
                              while (_bucket_iterator != _bucket_end_iterator && _bucket_iterator != _bucket_iterator_begin) {
                                   --_bucket_iterator;
                                   if (!_bucket_iterator->empty()) {
                                      _list_iterator = --_bucket_iterator->end();
                                      break;
                                   }
                              }
                         }
                         return *this;
                    }
                    iterator operator --(int) {
                         iterator temp = *this;
                         --(*this);
                         return temp;
                    
                    }
                    bool operator == (const iterator& other) const {
                         return _bucket_iterator == other._bucket_iterator and _list_iterator == other._list_iterator;
                    }
                    bool operator !=(const iterator& other) const {
                         return not (*this == other);
                    }

               private:
                    bucket_iterator_t _bucket_iterator, _bucket_iterator_begin, _bucket_end_iterator;
                    item_iterator_t _list_iterator;
          };

          iterator begin() {
               auto bucket_iter = _buckets.begin();
               auto bucket_end = _buckets.end();

               while (bucket_iter not_eq bucket_end) {
                    auto list_iter = bucket_iter->begin();

                    if (list_iter not_eq bucket_iter->end()) 
                         return iterator(bucket_iter, bucket_end, list_iter);

                    bucket_iter++;
               }
               return end();
          }

          iterator end() {
               return iterator(_buckets.end(), _buckets.end(), (_buckets.end() -1)->end());
          }

     private:     
          size_t _hash(const Key &key){
               return Hash{}(key) % _capacity;
          }
          void _rehash(size_t new_capacity){
               unordered_list<bucket_t> new_buckets(new_capacity);
               // this can be optimized without rehashing
               for (bucket_t& bucket : _buckets){
                    for (item_t& item : bucket){
                         size_t index = Hash{}(item.first) % new_capacity;
                         bucket_t &new_bucket = new_buckets[index];
                         new_bucket.push_back(std::move(item));
                    }
               }
               _buckets = std::move(new_buckets);
               _capacity = new_capacity;
          }
          
          float _load_factor = 0.75f;
          size_t _capacity = 0, _size = 0;
          unordered_list<bucket_t> _buckets;

          constexpr static size_t _default_bucket_number = 8; // the number of buckets used by default if an empty constructor is called
     };
 
}

int main(){
     ds::hash_table<int, int> table;
     for (int i = 1; i < 5; i++)
          table.emplace(i, 2 * i);
     
     
     // for (int i = 1; i < 5; i++)
     //      std::cout << table.at(i) << std::endl;

     std::cout << "begin" << std::endl;
     
     for (auto it = table.begin(); it != table.end(); it++)
          std::cout << it->first << " " << it->second << std::endl;

     std::cout << "finish" << std::endl;

}    
 