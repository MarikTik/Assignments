#ifndef SORTED_LIST_HPP_
#define SORTED_LIST_HPP_
#include "node.hpp"

template<typename T, typename Comparator>
class sorted_list{
     public:
          bool is_empty() const{
               return not _size;
          }
          size_t size() const{
               return _size;
          }
          void insert(T value){
               
          }


         
     private:
          node<T> _head;
          size_t _size = 0;
};


#endif