#ifndef SET_HPP
#define SET_HPP
#include "hash_table.hpp"
#include <variant>
#include <type_traits>

namespace ds{
     template<
     typename Key,
     typename Hash = std::hash<Key>,
     typename KeyEqual = std::equal_to<Key>,
     typename Allocator = std::allocator<Key>
     >
     class hash_set{
               template<typename> class basic_iterator;
               using hash_table_t = hash_table<Key, std::monostate, Hash, KeyEqual, Allocator>;
          public:

               using iterator = basic_iterator<typename hash_table_t::iterator>;
               using const_iterator = basic_iterator<typename hash_table_t::const_iterator>;

               /// @brief Default constructor.
               hash_set() = default;

               /// @brief Constructs a hash set with the specified capacity.
               /// @param capacity The initial capacity of the hash table.
               hash_set(size_t capacity) 
                    : _table(capacity)
               {
               }

               /// @brief Copy constructor.
               /// @param other The hash set to copy from.
               hash_set(const hash_set &other) 
                    : _table(other._table)
               {
               }

               /// @brief Move constructor.
               /// @param other The hash table to move from.
               hash_set(hash_set &&other) noexcept 
                    : _table(std::move(other._table))
               {
               }

               /// @brief Constructs a hash set with the specified items.
               /// @param items The list of items to insert into the hash set.
               hash_set(std::initializer_list<Key> keys) 
                    : _table(keys.size() * 2)
               {
                    for (auto &&key : keys) insert(key);
               }

               /// @brief Copy assignment operator.
               /// @param other The hash set to copy from.
               /// @return Reference to the current set table.
               hash_set &operator =(const hash_set &other){
                    if (this != &other) _table = other._table;
                    return *this;
               }

               /// @brief Move assignment operator.
               /// @param other The hash set to move from.
               /// @return Reference to the current hash set.
               hash_set &operator =(hash_set &&other) noexcept{
                    if (this != &other) _table = std::move(other._table);
                    return *this;
               }

               
               /// @brief Moves a new key into the hash set.
               /// @param key_value_pair The key-value pair to insert.
               template<typename TKey>
               void insert(TKey &&key){
                    _table.insert(std::forward<TKey>(key), std::monostate{});
               }

               /// @brief Inserts a range of keys into the hash table.
               /// @tparam InputIt An input iterator of any container.
               /// @param begin The iterator to the beginning of the range.
               /// @param end The iterator to the end of the range.
               template<typename InputIt>
               void insert(InputIt begin, InputIt end){
                    _table.insert(begin, end);
               }
                
               /// @brief Erases the key associated with the specified key.
               /// @param key The key to erase.
               void erase(const Key &key){
                    _table.erase(key);
               }

               /// @brief Seeks the specified key in the hash tablsete.
               /// @param key The key to search for.
               /// @return const_iterator to the key-value pair if it was found, cend() otherwise.
               const_iterator find(const Key &key) const{
                    return const_iterator(_table.find(key));
               }

               /// @brief Seeks the specified key in the hash set.
               /// @param key The key to search for.
               /// @return iterator to the key-value pair if it was found, end() otherwise.
               iterator find(const Key &key){
                    return iterator(_table.find(key));
               }
               
               /// @brief Checks if the specified key is in the hash set.
               /// @param key The key to search for.
               /// @return True if the key is in the hash table, false otherwise.
               inline bool contains(const Key &key) const{
                    return _table.contains(key);
               }
               
               /// @brief Returns the current capacity of the hash set.
               inline size_t capacity() const{
                    return _table.capacity();
               }
               
               /// @brief Returns whether the hash set is empty.
               /// @note This function has linear complexity or potentially quadratic.
               inline bool empty() const{
                    return _table.empty();
               }
               
               /// @brief Returns the number of elements in the hash set.
               /// @note This function has linear complexity or potentially quadratic.
               inline size_t size() const{
                    return _table.size();   
               }

               /// @brief Returns an iterator to the beginning of the hash set.
               iterator begin() { return iterator(_table.begin()); }
               
               /// @brief Returns an iterator to the end of the hash set.
               iterator end() { return iterator(_table.end()); }

               /// @brief Returns a const iterator to the beginning of the hash set.
               const_iterator cbegin() const { return const_iterator(_table.cbegin()); }

               /// @brief Returns a const iterator to the end of the hash set.
               const_iterator cend() const { return const_iterator(_table.cend()); }

               /// @brief Returns a const iterator to the beginning of the hash set.
               /// @note This function is provided for compatibility with the standard library. Use cbegin() instead.
               const_iterator begin() const { return cbegin(); }

               /// @brief Returns a const iterator to the end of the hash set.
               /// @note This function is provided for compatibility with the standard library. Use cend() instead.
               const_iterator end() const { return cend(); }
               
               void rehash(size_t new_capacity){
                    _table.rehash(new_capacity);
               }

               /// @brief Reserves the specified capacity for the hash set.
               /// @param new_capacity The new capacity to reserve. 
               void reserve(size_t new_capacity){
                    _table.reserve(new_capacity);
               }

               /// @brief Sets the maximum load factor of the hash set.
               void max_load_factor(float factor){
                    _table.max_load_factor(factor);
               }

               /// @brief Clears the hash set and releases memory.
               void clear(){
                    _table.clear();
               }

               
          private:
               hash_table<Key, std::monostate, Hash, KeyEqual, Allocator> _table;

               template<typename HashTableIterator>
               class basic_iterator{
                    using parent_iterator_t = HashTableIterator;
                    public:
                         using iterator_category = std::forward_iterator_tag;
                         using difference_type = std::ptrdiff_t;
                         using value_type = typename parent_iterator_t::value_type::first_type;
                         using pointer = std::conditional_t<std::is_const_v<parent_iterator_t>, const value_type*, value_type*>;
                         using reference = std::conditional_t<std::is_const_v<parent_iterator_t>, const value_type&, value_type&>;

                         basic_iterator(parent_iterator_t iter) : _iter(iter) {}
                         reference operator*() const { return _iter->first; }
                         pointer operator->() const { return &_iter->first; }
                         basic_iterator& operator++() { ++_iter; return *this; }
                         basic_iterator operator++(int) { auto copy = *this; ++_iter; return copy; }
                         bool operator ==(const basic_iterator &other) const { return _iter == other._iter; }
                         bool operator !=(const basic_iterator &other) const { return !(*this == other); }
                    private:
                         parent_iterator_t _iter;
               };
     };
}


#endif