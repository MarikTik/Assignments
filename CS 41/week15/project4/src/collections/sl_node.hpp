#ifndef SL_NODE_HPP
#define SL_NODE_HPP
#include <utility>

namespace ds{
     template<typename T>
     struct sl_node{
          template<typename... Args>
          sl_node(Args&&... args) : data(std::forward<Args>(args)...)
          {   
          }
          sl_node(sl_node &&other) noexcept 
               : next(other.next), data(std::move(other.data))
          {
               other.next = nullptr;
          }
          sl_node &operator=(sl_node &&other) noexcept{
               if (this != &other){
                    next = other.next;
                    data = std::move(other.data);
                    other.next = nullptr;
               }
               return *this;
          }
           
          sl_node<T> *next = nullptr;
          T data;
     };
}
#endif