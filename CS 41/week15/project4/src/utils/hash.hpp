#ifndef HASH_HPP
#define HASH_HPP
#include <string>

template<typename>
struct custom_hash{};

template<>
struct custom_hash<std::string>
{
     size_t operator ()(const std::string& str){
          size_t hash = 0;
          for (char c : str) hash += c;
          return hash;
     }
};


#endif