#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include <functional>
#include <type_traits>

template<typename T>
class list{
     public:
          void push_back(T value){
               auto *new_node = new node<T>(value);
               if (not _head) {
                    _head = new_node;
               }
               else if (not _tail) {
                    _tail = new_node;
                    _tail->attach_previous(_head);
               }
               else{
                    _tail->attach_next(new_node);
                    _tail = new_node;
               }
          }         

          void clear(){
               while(_head){
                    auto* previous = _head;
                    _head = _head->next;
                    delete previous;
               }

          }

          class iterator{
               public:
                    T &operator *() const{
                         return current->data;
                    }
                    iterator &operator ++(){
                         current = current->next;
                         return *this;
                    }
                    bool operator == (const iterator &other) const{
                         return current == other.current;
                    }
                    bool operator != (const iterator &other) const{
                         return current != other.current;
                    }
               private:
                    node<T> *current;
          };

          iterator begin() const { return iterator(_head); }
          iterator end() const { return iterator(nullptr); }
         
          ~list(){ clear(); }
     private:
          node<T> *_head = nullptr, *_tail = nullptr;
};


#endif