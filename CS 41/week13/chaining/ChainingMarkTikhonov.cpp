// This implementation features a bigger set of functionality, which will be used in my project4
// for writing the iterators, I consulted the webpage: https://en.cppreference.com/w/cpp/iterator
// and some additional resources, so that my data structures resemble their counterparts from the 
// stl.

#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cassert>

template<typename T>
struct dl_node{
     public:
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
class list{
     public:
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

          template<typename Predicate>
          void remove_if(Predicate predicate, bool remove_all=false){
               for (const auto *ptr = _head; ptr; ptr = ptr->next){
                    if (std::invoke(predicate, ptr->data)){
                         auto* next = ptr->next;
                         if (ptr == _head){
                              delete _head;
                              _head = next;
                         }
                         else{
                              auto* previous = ptr->previous;
                              previous->attach_next(next);
                              delete ptr;
                         }
                         if (not remove_all) break;
                    }
               }
          }

          void clear(){
               for (auto *previous = _head; previous; previous = previous->next) 
                    delete previous;
          }
          
          class iterator {
          public:

               using iterator_category = std::bidirectional_iterator_tag;
               using difference_type = std::ptrdiff_t;
               using value_type = T;
               using pointer = T*;
               using reference = T&;

              
               iterator(dl_node<T> *head) : current(head) {}

               T& operator*() const {
                    return current->data;
               }
              
               iterator& operator++() {
                    current = current->next;
                    return *this;
               }
              
               iterator operator++(int) {
                    iterator tmp = *this;
                    current = current->next;
                    return tmp;
               }

               iterator& operator--() {
                    current = current->previous;
                    return *this;
               }
              
               iterator operator--(int) {
                    iterator tmp = *this;
                    current = current->previous;
                    return tmp;
               }

               bool operator==(const iterator &other) const {
                    return current == other.current;
               }
              
               bool operator!=(const iterator &other) const {
                    return current != other.current;
               }
               
          private:
              dl_node<T> *current;
          };


          iterator begin() const { return iterator(_head); }
          iterator end() const { return iterator(nullptr); }
         
          ~list(){ clear(); }
     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
};
 
template <typename T>
class dynamic_array{
     public:
          dynamic_array() = default;

          dynamic_array(size_t capacity)
               : _array(new T[capacity]), _capacity(capacity), _size(0)
          {               
               assert(capacity > 0);
          }

          dynamic_array(std::initializer_list<T> list){
               reserve(list.size());
               std::move(list.begin(), list.end(), _array);
          }

          dynamic_array(dynamic_array&& other) noexcept
               : _size(other._size), _capacity(other._capacity), _array(other._array) {
               other._array = nullptr;
               other._size = 0;
               other._capacity = 0;
          }
          dynamic_array& operator=(dynamic_array&& other) noexcept {
               if (this != &other) {
                    delete[] _array; 
                    _array = other._array;
                    _size = other._size;
                    _capacity = other._capacity;
                    other._array = nullptr;
                    other._size = 0;
                    other._capacity = 0;
               }
               return *this;
          }
          template<typename Arg>
          void push_back(Arg &&value){
               if (_size == _capacity) reserve((_capacity == 0 ? 1 : _capacity) * 2);
               _array[_size++] = std::forward<T>(value);
          }

          T& operator[](size_t index){
               if (index >= _capacity)
                    throw std::out_of_range("index out of bounds");
               return _array[index];
          }
          void reserve(size_t capacity){
               if (capacity > _capacity) {
                    T* new_array = new T[capacity];
                    if (_capacity > 0)
                    {
                         T* begin = _array, *end = _array + _size;
                         if constexpr (std::is_move_constructible_v<T>)
                              std::move(begin, end, new_array);  
                         else 
                              std::copy(begin, end, new_array); 
                         delete[] _array;   
                    }
                    _array = new_array;   
                    _capacity = capacity;   
               }
          }

          inline size_t size() const{
               return _size;
          }

          class iterator {
          public:
               using iterator_category = std::random_access_iterator_tag;
               using value_type = T;
               using difference_type = std::ptrdiff_t;
               using pointer = T*;
               using reference = T&;

               iterator(T* ptr) : _ptr(ptr) {}

               reference operator *() const { 
                   return *_ptr;
               }

               pointer operator ->() const { 
                   return _ptr;
               }

               iterator& operator ++() {
                   ++_ptr;
                   return *this;
               }

               iterator operator ++(int) {
                   iterator temp = *this;
                   ++(*this);
                   return temp;
               }

               iterator& operator --() {
                   --_ptr;
                   return *this;
               }

               iterator operator --(int) { 
                   iterator temp = *this;
                   --(*this);
                   return temp;
               }

               iterator& operator +=(difference_type n) { 
                   _ptr += n;
                   return *this;
               }

               iterator& operator -=(difference_type n) {
                   _ptr -= n;
                   return *this;
               }

               iterator operator +(difference_type n) const {
                   return iterator(_ptr + n);
               }

               iterator operator -(difference_type n) const {
                   return iterator(_ptr - n);
               }

               difference_type operator -(const iterator& other) const {
                   return _ptr - other._ptr;
               }

               bool operator ==(const iterator& other) const {
                   return _ptr == other._ptr;
               }

               bool operator !=(const iterator& other) const {
                   return _ptr != other._ptr;
               }

               bool operator <(const iterator& other) const {
                   return _ptr < other._ptr;
               }

               bool operator >(const iterator& other) const {
                   return _ptr > other._ptr;
               }

               bool operator <=(const iterator& other) const {
                   return _ptr <= other._ptr;
               }

               bool operator >=(const iterator& other) const {
                   return _ptr >= other._ptr;
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
          T *_array = nullptr;
          size_t _capacity = 0, _size = 0;

};

template<
     typename Key,
     typename Value,
     typename Hash = std::hash<Key>
>
class hash_table{
     using item_t = std::pair<Key, Value>;
     using bucket_t = list<item_t>;

     public:

          hash_table()
               : _capacity(_default_bucket_number),
                 _buffer(_default_bucket_number)
          {
          }
          hash_table(size_t capacity)
               : _capacity(capacity),
               _buffer(capacity)
          {
          }

          hash_table(std::initializer_list<item_t> items)
               : _capacity(items.size()),
               _buffer(std::move(items)),
               _size(_capacity)
          {
          }

          template<typename Arg1, typename Arg2>
          void emplace(Arg1&& key, Arg2&& value) {
               if (_size + 1 > _capacity * _load_factor){ // check if rehashing is needed
                    _rehash(_capacity * 2);
               }
               else{
                    size_t bucket_index = _hash(key);
                    _buffer[bucket_index].push_back(
                        std::make_pair(std::forward<Arg1>(key), std::forward<Arg2>(value))
                    );
               }
               _size++;
          }

          void remove(const Key &key){
               size_t bucket_index = _hash(key);
               _buffer[bucket_index].remove_if([&key](const auto& item){
                    return item.first == key;
               });
               _size--;
          }

          Value& at(const Key &key){
               size_t bucket_index = _hash(key);
               bucket_t &bucket = _buffer[bucket_index];
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
               bucket_t &bucket = _buffer[bucket_index];
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
     private:     
          size_t _hash(const Key &key){
               return Hash{}(key) % _capacity;
          }
          void _rehash(size_t new_capacity){
               dynamic_array<bucket_t> new_buffer(new_capacity);
               
               for (size_t i = 0; i < _capacity; i++) {
                    for (auto& item : _buffer[i]) {
                         size_t new_index = Hash{}(item.first) % new_capacity;
                         new_buffer[new_index].push_back(std::move(item));
                    }
               }
               _buffer = std::move(new_buffer);
               _capacity = new_capacity;
          }
          
          float _load_factor = 0.75f;
          size_t _capacity = 0, _size = 0;
          dynamic_array<bucket_t> _buffer;

          constexpr static size_t _default_bucket_number = 8; // the number of buckets used by default if an empty constructor is called
};
 
int main(){
     hash_table<int, int> table;
     for (int i = 0; i < 7; i++)
          table.emplace(i, 2 * i);
     
     std::cout << table.size();
}    