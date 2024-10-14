#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include "unordered_list.hpp"
#include "linked_list.hpp"
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
          public:
               hash_table() 
                    : _table() 
               {
               }

               hash_table(size_t capacity) 
                    : _table(capacity)
               {
               }
               hash_table(const hash_table &other) 
                    : _table(other._table)
               {
               }

               hash_table(hash_table &&other) noexcept 
                    : _table(std::move(other._table))
               {
               }

               hash_table(std::initializer_list<item_t> items) 
                    : _table(items.size() * 2)
               {
                    for (auto &&item : items) emplace(std::move(item));
               }
               hash_table &operator =(const hash_table &other){
                    if (this != &other) _table = other._table;
                    return *this;
               }

               hash_table &operator =(hash_table &&other) noexcept{
                    if (this != &other) _table = std::move(other._table);
                    return *this;
               }

               template<typename... Args>
               void emplace(const Key &key, Args &&...args) {
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
               void insert(item_t &&key_value_pair){
                    auto &key = key_value_pair.first;
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];

                    for (auto &kvp : chain) 
                         if (KeyEqual{}(kvp.first, key))  
                              return;
                    
                    chain.emplace_back(std::move(key_value_pair));
               }
               void insert(const item_t &key_value_pair){
                    insert(item_t{key_value_pair});
               }

               const Value &at(const Key &key) const{
                    size_t index = Hash{}(key) % _table.capacity();
                    const chain_t &chain = _table[index];
                    for (const auto &kvp : chain)
                         if (KeyEqual{}(kvp.first, key)) 
                              return kvp.second;
                    throw std::out_of_range("key not found");
               }
               Value &at(const Key &key){
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];
                    for (auto &kvp : chain)
                         if (KeyEqual{}(kvp.first, key)) 
                              return kvp.second;
                    throw std::out_of_range("key not found");
               }
               Value& operator[](const Key& key) {
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t& chain = _table[index];

               
                    for (auto& kvp : chain) 
                         if (KeyEqual{}(kvp.first, key))  
                              return kvp.second;   

                    chain.emplace_back(key, Value{}); // insert a new element with a default-constructed value
                    return chain.back().second;
               }

               void reserve(size_t capacity){
                    _table.reserve(capacity);
                    // rehash required
               }

               void shrink_to_fit(){
                    _table.shrink_to_fit();
                     // rehash required
               }

               void remove(const Key &key){
                    size_t index = Hash{}(key) % _table.capacity();
                    chain_t &chain = _table[index];
                    chain.remove_if([&key](const auto &key_value_pair){
                         return KeyEqual{}(key_value_pair.first, key);
                    });
               }

               float load_factor() const{
                    return static_cast<float>(_table.size()) / static_cast<float>(_table.capacity());
               }
               class iterator{
                    public:
                         using iterator_category = std::forward_iterator_tag;
                         using difference_type = std::ptrdiff_t;
                         using value_type = item_t;
                         using pointer = item_t*;
                         using reference = item_t&;

                         using element_iterator_t = typename chain_t::iterator;
                         using chain_iterator_t = typename unordered_list<chain_t, Allocator>::iterator;

                         iterator(chain_iterator_t chain_it, chain_iterator_t chain_end)
                              : _chain_it(chain_it),
                                _chain_end(chain_end),
                                _element_it(chain_it->begin())
                         {
                              if (_chain_it != _chain_end) {
                                    _element_it = _chain_it->begin();
                                   advance();
                              }
                         }
                         reference operator*() const {
                              return *_element_it;
                         }
                         pointer operator->() const {
                              return &(*_element_it);
                         }
                         iterator &operator ++(){
                              ++_element_it;
                              if (_element_it == _chain_it->end()) {
                                   ++_chain_it;
                                   advance();
                              }
                              return *this;
                         }
                         iterator operator++(int) {
                              iterator temp = *this;
                              ++(*this);
                              return temp;
                         }
                         bool operator == (const iterator &other) const{
                              return _chain_it == other._chain_it and _element_it == other._element_it;
                         }
                         bool operator != (const iterator &other) const{
                              return not (*this == other);
                         }
                    private:
                         chain_iterator_t _chain_it;
                         chain_iterator_t _chain_end;
                         element_iterator_t _element_it;

                         void advance(){
                              for (; _chain_it != _chain_end and _element_it == _chain_it->end(); ++_chain_it) 
                                   if (_chain_it != _chain_end) _element_it = _chain_it->begin();
                         }
               };

          private:
               size_t _size;
               unordered_list<chain_t, chain_allocator_t> _table;
               constexpr static float _rehash_coefficient = 0.75f;
     };
}

#endif