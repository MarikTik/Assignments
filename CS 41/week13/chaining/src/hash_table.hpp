// #ifndef HASH_TABLE_HPP
// #define HASH_TABLE_HPP
// #include "unordered_list.hpp"
// #include "linked_list.hpp"
// namespace ds{
//      template<
//           typename Key,
//           typename Value,
//           typename Hash = std::hash<Key>,
//           typename KeyEqual = std::equal_to<Key>,
//           typename Allocator = std::allocator<std::pair<const Key, Value> >
//      >
//      class hash_table{
//                using item = std::pair<const Key, Value>;
//                using chain = linked_list<item>;
//           public:
//                hash_table() : _table() {}
//                hash_table(size_t capacity) : _table(capacity) {}
//                hash_table(const hash_table &other) : _table(other._table) {}
//                hash_table(hash_table &&other) : _table(std::move(other._table)) {}
//                hash_table &operator =(const hash_table &other){
//                     if (this == &other) return *this;
//                     _table = other._table;
//                     return *this;
//                }
//                hash_table &operator =(hash_table &&other){
//                     if (this == &other) return *this;
//                     _table = std::move(other._table);
//                     return *this;
//                }
//                template<typename... Args>
//                void emplace(Args&&... args) {
//                     std::pair<const Key, Value> new_pair(std::forward<Args>(args)...);

//                     size_t hash_value = _hasher(new_pair.first) % _table.capacity();
//                     chain &bucket = _table[hash_value];

//                     // Check if the key already exists, and don't insert if it does
//                     for (auto &kv : bucket) 
//                          if (KeyEqualP{}(kv.first, new_pair.first))  
//                               return;

//                     // Insert the new pair into the chain
//                     bucket.push_back(std::move(new_pair)); // Move new_pair into the bucket
//                }
//                void insert(const std::pair<const Key, Value> &pair){

//                }
//                Value &at(const Key &key) const{
//                }
//                Value &operator [](const Key &key){
//                }
//                class iterator{

//                };
//           private:
//                unordered_list<chain, Allocator> _table;


//      };
// }


// //  void emplace(const Key &key, const Value &value){
// //                     size_t index = Hash{}(key) % _table.capacity();
// //                     chain &list = _table[index];
// //                     for (auto &pair : list){
// //                          if (KeyEqual{}(pair.first, key)){
// //                               pair.second = value;
// //                               return;
// //                          }
// //                     }
// //                     list.push_back(std::make_pair(key, value));
// //                }
// //                Value &at(const Key &key) const{
// //                     size_t index = Hash{}(key) % _table.capacity();
// //                     chain &list = _table[index];
// //                     for (auto &pair : list){
// //                          if (KeyEqual{}(pair.first, key)){
// //                               return pair.second;
// //                          }
// //                     }
// //                     throw std::out_of_range("key not found");
// //                }
// //                Value &operator [](const Key &key){
// //                     size_t index = Hash{}(key) % _table.capacity();
// //                     chain &list = _table[index];
// //                     for (auto &pair : list){
// //                          if (KeyEqual{}(pair.first, key)){
// //                               return pair.second;
// //                          }
// //                     }
// //                     list.push_back(std::make_pair(key, Value{}));
// //                     return list.back().second;
// //                }
// #endif