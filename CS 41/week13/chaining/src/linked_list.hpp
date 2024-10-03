#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include "dl_node.hpp"
#include <limits>

namespace ds{
     template<typename T>
     class linked_list{
     public:

          linked_list() {};
          linked_list(linked_list &&other) : _head(other._head), _tail(other._tail)
          {
               other._head = other._tail = nullptr;
          }
          linked_list &operator = (linked_list &&other){
               _head = other._head, _tail = other._tail;
               other._head = other._tail = nullptr;
          }

          /// @brief inserts a new element at the end of the list
          /// @tparam Arg the type of the value to be inserted
          /// @param value the value to be inserted
          /// @return void
          template<typename Arg>
          void push_back(Arg &&value){
               auto *node = new dl_node<T>(std::forward<Arg>(value));
               if (not _head) {
                    _head = _tail = node;
               }
               else{
                    _tail->attach_next(node);
                    _tail = node;
               }
          }   

          /// @brief inserts a new element at the beginning of the list
          /// @tparam Arg the type of the value to be inserted
          /// @param value the value to be inserted
          /// @return void
          template<typename Arg>
          void push_front(Arg &&value){
               auto *node = new dl_node<T>(std::forward<Arg>(value));
               if (not _head){
                    _head = _tail = node;
               }
               else{
                    _head->attach_previous(node);
                    _head = node;
               }
          }

          /// @brief removes the first n elements from an array that satisfy a predicate
          /// @tparam Predicate the type of the predicate to be used
          /// @param predicate the predicate to be used to remove elements
          /// @param n the number of elements to remove, if set to 0, all elements that satisfy the predicate will be removed
          /// @return void
          template<typename Predicate>
          void remove(Predicate predicate, size_t n = 1){
               if (empty()) return;
               if (n == 0) n = std::numeric_limits<size_t>::max();
               
               for (dl_node<T> *_ptr = _head, *next; _ptr; _ptr = next){
                    next = _ptr->next;
                    if (std::invoke(predicate, _ptr->data)){
                         if (_ptr == _head){
                              delete _head;
                              _head = next;
                              if (_head) _head->previous = nullptr;
                         }
                         else{
                              auto *previous = _ptr->previous;
                              previous->attach_next(next);
                              delete _ptr;
                         }
                         if (--n == 0) return;
                    }
               }
          }

          bool empty() const{
               return not _head;
          }

          void clear(){
               for (auto *_ptr = _head; _ptr;){
                    auto *next = _ptr->next;
                    delete _ptr;
                    _ptr = next;
               }
               _head = _tail = nullptr;
          }

          class iterator {
               public:
                    using iterator_category = std::bidirectional_iterator_tag;
                    using difference_type = std::ptrdiff_t;
                    using value_type = T;
                    using pointer = value_type *;
                    using reference = value_type &;

                    iterator() = default;
                    iterator(dl_node<T> *head) : _ptr(head) {}
                    reference& operator *() const {return _ptr->data;}
                    iterator& operator ++() {_ptr = _ptr->next; return *this;}
                    iterator operator ++(int) {iterator tmp = *this; _ptr = _ptr->next; return tmp;}
                    iterator& operator --() {_ptr = _ptr->previous; return *this;}
                    iterator operator --(int) {iterator tmp = *this; _ptr = _ptr->previous; return tmp;}
                    bool operator ==(const iterator &other) const {return _ptr == other._ptr;}
                    bool operator !=(const iterator &other) const {return _ptr != other._ptr;}

               private:
                   dl_node<T> *_ptr = nullptr;
          };
          iterator begin() const { return iterator(_head); }
          iterator end() const { return iterator(nullptr); }
       

          ~linked_list(){ clear(); }

     private:
          dl_node<T> *_head = nullptr, *_tail = nullptr;
     };
}
#endif