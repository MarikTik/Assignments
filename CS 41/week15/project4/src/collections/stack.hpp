#ifndef STACK_HPP
#define STACK_HPP
#include "../utils/sl_node.hpp"

template<typename T>
class stack{
     public:
          bool is_empty() const{
               return not _size;
          }

          template<typename TItem>
          void push(TItem item){
               auto node = new sl_node<T>(std::forward<TItem>(item));
               node->next = _top;
               _top = node;
               _size ++;
          }
          T pop(){
               if (is_empty()) throw std::underflow_error("attempted to pop an element from stack, but it is empty");

               T value = _top->data;
               auto ptr = _top;
               _top = _top->next;
               delete ptr;
               _size --;
               return value;
          }
          T peek() const{
               if (is_empty()) throw std::underflow_error("attempted to peek an element from stack, but it is empty");
               return _top->data;
          }
          inline size_t size() const{
               return _size;
          }
          ~stack(){
               while(_size--)
               {
                    auto ptr = _top;
                    _top = _top->next;
                    delete ptr;
               }
          }
     private:
          sl_node<T> *_top = nullptr;
          size_t _size = 0;
};


#endif