#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <cstdint>
#include "list.hpp"
// #include "dynamic_array.hpp"
// #include <unordered_map>

 
template<typename TKey, typename TValue>
class hash_table{
     using item_t = std::pair<TKey, TValue>;
     using bucket_t = list<item_t>;

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

          size_t bucket_index = _hash(std::forward<TKeyForward>(key));
          _buffer[bucket_index].remove(

          );
          _size--;
     }
     size_t size() const{
          return _size;
     }

     ~hash_table(){
          delete[] _buffer; 
     }
     private:
          
          size_t _hash(const TKey &key){
               return std::hash<TKey>(key) % _capacity;
          }

          bucket_t *_buffer;
          size_t _capacity, _size;
};

#endif