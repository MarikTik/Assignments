#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct node{
     template<typename TForward>
     node(TForward &&val) : data(std::forward<TForward>(val))
     {
     }
     void attach_next(node<T> *next_node){
          if (not next_node) return;
          next_node->previous = this;
          this->next = next_node;
     }
     void attach_previous(node<T> *previous_node){
          if (not previous_node) return;
          previous_node->next = this;
          this->previous = previous_node;
     }
     T data;
     node<T> *previous;
     node<T> *next;
};

#endif