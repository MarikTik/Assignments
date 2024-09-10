#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct node{
     node(T val) : value(val)
     {
     }
     void attach_next(node<T> *next_node){
          next_node->previous = this;
          this->next = next_node;
     }
     void attach_previous(node<T> *previous_node){
          previous_node->next = this;
          this->previous = previous_node;
     }
     T value;
     node<T> *previous;
     node<T> *next;
};

#endif