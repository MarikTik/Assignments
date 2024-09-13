#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <cstdint>
#include <algorithm>
#include "list.hpp"
#include "../utils/hash.hpp"

template<
     typename TKey,
     typename TValue,
     typename Hash = std::hash<TKey>
>
class hash_table{
     using item_t = std::pair<TKey, TValue>;
     using bucket_t = list<item_t>;

     public:
       
          hash_table(size_t capacity)
               : _capacity(capacity),
               _buffer(new bucket_t[capacity])
               
          {
          }

          hash_table(std::initializer_list<item_t> items)
               : _capacity(items.size()),
               _buffer(new bucket_t[items.size()]),
               _size(_capacity)
          {
               for (const item_t &item : items){
                   emplace(std::move(item.first), std::move(item.second));
               }
          }

          template<typename Key, typename Value>
          void emplace(Key&& key, Value&& value) {
               size_t bucket_index = _hash(key);
               _buffer[bucket_index].push_back(
                   std::make_pair(std::forward<Key>(key), std::forward<Value>(value))
               );
               _size++;
          }

          void remove(const TKey &key){
               size_t bucket_index = _hash(key);
               _buffer[bucket_index].remove_if([&key](const auto& item){
                    return item.first == key;
               });
               _size--;
          }

          TValue& at(const TKey &key){
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

          bool contains(const TKey &key){
               size_t bucket_index = _hash(key);
               bucket_t &bucket = _buffer[bucket_index];
               auto iterator = std::find_if(bucket.begin(), bucket.end(),
                    [&key](const item_t& item){
                         return item.first == key;
                    }
               );
               return iterator != bucket.end();
          }
          size_t size() const{
               return _size;
          }

          ~hash_table(){
               delete[] _buffer; 
          }
          
     private:     
          size_t _hash(const TKey &key){
               return Hash{}(key) % _capacity;
          }
          
         
          bucket_t *_buffer;
          size_t _capacity = 0, _size = 0;
};

template<typename TValue>
using string_map = hash_table<std::string, TValue, custom_hash<std::string>>;

#endif