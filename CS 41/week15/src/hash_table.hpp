#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <cstdint>
#include <algorithm>
#include "list.hpp"

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
               : _buffer(new bucket_t[capacity]),
               _capacity(capacity),
               _size(0)
          {

          }
          template<typename TKeyForward, typename TValueForward>
          void emplace(TKeyForward&& key, TValueForward&& value) {
               size_t bucket_index = _hash(key);

               _buffer[bucket_index].push_back(
                   std::make_pair(std::forward<TKeyForward>(key), std::forward<TValueForward>(value))
               );
     
               _size++;
          }

          template<typename TKeyForward>
          void remove(TKeyForward &&key){
               size_t bucket_index = _hash(key);
               _buffer[bucket_index].remove_if([&key](auto pair){
                    return pair.first == key;
               });
               _size--;
          }

          template<typename TKeyForward>
          TValue& at(TKeyForward &&key){
               size_t bucket_index = _hash(key);
               bucket_t &bucket = _buffer[bucket_index];
               auto iterator = std::find_if(bucket.begin(), bucket.end(),
               [&key](const item_t& item){
                    return item.first == key;
               });
               if (iterator == bucket.end()) throw std::out_of_range("key error: key not found in hash table");
               return (*iterator).second;
          }
          size_t size() const{
               return _size;
          }

          ~hash_table(){
               delete[] _buffer; 
          }
          private:
          
          size_t _hash(TKey &key){
               return Hash{}(key) % _capacity;
          }

          bucket_t *_buffer;
          size_t _capacity, _size;
};

#endif