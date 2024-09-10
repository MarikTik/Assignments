#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <cstdint>
#include "list.hpp"
#include "dynamic_array.hpp"
#include <unordered_map>

 
template<typename TKey, typename TValue>
class hash_table{
     using bucket_t = list<TValue>;

     void emplace(TValue &&value){

     }

     ~hash_table(){
          
           
     }
     private:
          dynamic_array<bucket_t> _buffer;
};

#endif