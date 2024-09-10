#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include <functional>
#include <type_traits>

template<typename T>
class list{
     public:
          template<typename TForward>
          void push_back(TForward &&value){
               auto *new_node = new node<T>(std::forward<TForward>(value));
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

          template<typename Predicate>
          void remove_if(Predicate predicate, bool remove_all=false){
               auto* ptr = _head;
               while(ptr){
                    if (std::invoke(predicate, ptr->data)){
                         auto* next = ptr->next;
                         if (ptr == _head){
                              delete _head;
                              _head = next;
                         }
                         else{
                              auto* previous = ptr->previous;
                              previous->attach_next(next);
                              delete ptr;
                         }

                         if (not remove_all) break;
                    }
                    ptr = ptr->next;
               }
          }

          template<typename TForward>
          void remove(TForward &&value){
               remove_if([&value](const T& val){
                    return value == val;
               });
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
                    iterator(node<T> *head){
                         current = head;
                    }
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