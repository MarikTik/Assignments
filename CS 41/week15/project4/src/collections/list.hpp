#ifndef LIST_HPP
#define LIST_HPP
#include "../utils/dl_node.hpp"
#include <functional>
#include <type_traits>

template<typename T>
class list{
     public:
          template<typename TForward>
          void push_back(TForward &&value){
               auto *node = new dl_node<T>(std::forward<TForward>(value));
               if (not _head) {
                    _head = node;
               }
               else if (not _tail) {
                    _tail = node;
                    _tail->attach_previous(_head);
               }
               else{
                    _tail->attach_next(node);
                    _tail = node;
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

          class iterator {
          public:
               using iterator_category = std::bidirectional_iterator_tag;
               using difference_type = std::ptrdiff_t;
               using value_type = T;
               using pointer = T*;
               using reference = T&;

              
               iterator(dl_node<T> *head) : current(head) {}

               T& operator*() const {
                    return current->data;
               }
              
               iterator& operator++() {
                    current = current->next;
                    return *this;
               }
              
               iterator operator++(int) {
                    iterator tmp = *this;
                    current = current->next;
                    return tmp;
               }

               iterator& operator--() {
                    current = current->previous;
                    return *this;
               }
              
               iterator operator--(int) {
                    iterator tmp = *this;
                    current = current->previous;
                    return tmp;
               }

               bool operator==(const iterator &other) const {
                    return current == other.current;
               }
              
               bool operator!=(const iterator &other) const {
                    return current != other.current;
               }
               
          private:
              dl_node<T> *current;
          };


          iterator begin() const { return iterator(_head); }
          iterator end() const { return iterator(nullptr); }
         
          ~list(){ clear(); }
     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
};


#endif