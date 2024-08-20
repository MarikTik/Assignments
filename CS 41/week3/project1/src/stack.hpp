#ifndef STACK_HPP_
#define STACK_HPP_
#include <stdexcept>
#include "node.hpp"

template<typename T>
class stack{
     public:
          bool is_empty() const{
               return not _size;
          }
          size_t size() const{
               return _size;
          }
          void push(T item){
               auto new_node = new node<T>(item);
               new_node->next = _top;
               _top = new_node;
               _size ++;
          }
          T pop(){
               if (is_empty())
                    throw std::underflow_error("attempted to pop an element from stack, but it is empty");

               T value = _top->data;
               auto ptr = _top;
               _top = _top->next;
               delete ptr;
               _size --;
               return value;
          }
          void clear(){
               while(_size--)
               {
                    auto ptr = _top;
                    _top = _top->next;
                    delete ptr;
               }
          }
          ~stack(){
               clear();
          }    
     private:
          node<T> *_top;
          size_t _size = 0;
};

#endif