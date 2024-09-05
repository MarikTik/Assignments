#ifndef SORTED_NODE_ORDER_HPP
#define SORTED_NODE_ORDER_HPP
#include "node.hpp"
#include <ostream>
// sorts by values of type T, and maintains track U type values
template<typename T, typename U>
class sorted_node_order{
     public:
          template<typename Comparator>
          void insert(T _t_head_value, U _u_head_value, Comparator comparator){
               node<T> *t_node = new node<T>(_t_head_value);
               node<U> *u_node = new node<U>(_u_head_value);

               if (not _t_head)
               {
                    _t_head = t_node;
                    _u_head = u_node;
                    return;
               }
               node<T> *t_current = _t_head;
               node<T> *t_previous = nullptr;

               node<U> *u_current = _u_head;
               node<U> *u_previous = nullptr;

               while (t_current and comparator(t_current->data, _t_head_value)){
                    t_previous = t_current;
                    t_current = t_current->next;

                    u_previous = u_current;
                    u_current = u_current->next;
               }
     
               if (not t_previous) // the comparator returned false immediately, hence swap head with new node
               {
                    t_node->next = _t_head;
                    _t_head->previous = t_node;
                    _t_head = t_node;

                    u_node->next = _u_head;
                    _u_head->previous = u_node;
                    _u_head = u_node;
               }
               else if (t_current){ // the comparator returned false hence there is a continuation of the list to attach
                    t_previous->next = t_node;
                    t_node->previous = t_previous;
                    t_node->next = t_current;
                    t_current->previous = t_node;

                    u_previous->next = u_node;
                    u_node->previous = u_previous;
                    u_node->next = u_current;
                    u_current->previous = u_node;
               }
               else{ // end of list reached, so the new node is the last one
                    t_previous->next = t_node;
                    t_node->previous = t_previous;

                    u_previous->next = u_node;
                    u_node->previous = u_previous;
               }
          }

          friend std::ostream & operator << (std::ostream &os, const sorted_node_order<T, U> &order){
               node<T> *t_ptr = order._t_head;
               node<U> *u_ptr = order._u_head;

               if (not t_ptr)
                    return os;

               os << t_ptr->data << " - " << u_ptr->data;
               t_ptr = t_ptr->next;
               u_ptr = u_ptr->next;
               while (t_ptr){
                    os << ", " << t_ptr->data << " - " << u_ptr->data;
                    t_ptr = t_ptr->next;
                    u_ptr = u_ptr->next;
               }
               return os;
          }
          void clear(){
               node<T> *t_current = _t_head;
               node<T> *t_next = nullptr;
               while (t_current){
                    t_next = t_current->next;
                    delete t_current;
                    t_current = t_next;
               }
               node<U> *u_current = _u_head;
               node<U> *u_next = nullptr;
               while (u_current){
                    u_next = u_current->next;
                    delete u_current;
                    u_current = u_next;
               }
          }
          ~sorted_node_order(){
               clear();
          }
     private:
          node<T>* _t_head = nullptr;
          node<U>* _u_head = nullptr;
};

// template<typename T, typename Comparator>
// void insert_sorted(node<T> *&head,T value, Comparator &&comparator){
//      node<T> *new_node = new node<T>(value);
//      if (not head)
//      {
//           head = new_node;
//           return;
//      } 
//      node<T> *current = head;
//      node<T> *previous = nullptr;
//      while (current and comparator(current->data, value)){
//           previous = current;
//           current = current->next;
//      }
//      if (not previous) // the comparator returned false immediately, hence swap head with new node
//      {
//           new_node->next = head;
//           head->previous = new_node;
//           head = new_node;
//      }
//      else if (current){ // _comparator returned false hence there is a continuation of the list to attach
//           previous->next = new_node;
//           new_node->previous = previous;
//           new_node->next = current;
//           current->previous = new_node;
//      }
//      else{ // end of list reached, so the new node is the last one
//           previous->next = new_node;
//           new_node->previous = previous;
//      }
// }
#endif