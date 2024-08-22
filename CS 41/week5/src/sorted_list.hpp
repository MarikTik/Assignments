#ifndef SORTED_LIST_HPP_
#define SORTED_LIST_HPP_
#include "node.hpp"
#include <functional>
#include <ostream>

// this implementation of linked list uses doubly linked list, as required by the assignment
template<typename T>
class sorted_list{
     using comparator_t = std::function<bool(T, T)>;
     public:
          sorted_list(comparator_t comparator)
               : _comparator(comparator)
          {
          }

          bool is_empty() const{
               return not _size;
          }
          size_t size() const{
               return _size;
          }
          void insert(T value){
               node<T> *new_node = new node<T>(value);
               if (not _head)
               {
                    _head = new_node;
                    return;
               } 
               node<T> *current = _head;
               node<T> *previous = nullptr;

               while (current and _comparator(current->data, value)){
                    previous = current;
                    current = current->next;
               }
               if (not previous) // the comparator returned false immediately, hence swap head with new node
               {
                    new_node->next = _head;
                    _head->previous = new_node;
                    _head = new_node;
               }
               else if (current){ // _comparator returned false hence there is a continuation of the list to attach
                    previous->next = new_node;
                    new_node->previous = previous;
                    new_node->next = current;
                    current->previous = new_node;
               }
               else{ // end of list reached, so the new node is the last one
                    previous->next = new_node;
                    new_node->previous = previous;
               }

          }

          friend std::ostream &operator << (std::ostream& os, const sorted_list<T>& lst){
               const auto *ptr = lst._head;
               if (not ptr)
                    return os;
               os << ptr->data;
               ptr = ptr->next;
               while(ptr){
                    os << ", " << ptr->data;
                    ptr = ptr->next;
               }
               return os;
          }

          ~sorted_list(){
               auto *ptr = _head;
               while (ptr){
                    auto *next = ptr->next;
                    delete ptr;
                    ptr = next;
               }
          }


         
     private:
          node<T> *_head = nullptr;
          comparator_t _comparator;
          size_t _size = 0;
};


#endif