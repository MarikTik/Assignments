#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include "unordered_list.hpp"
#include "linked_list.hpp"
#include <type_traits>
#include <algorithm>

namespace ds{
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
 

#endif