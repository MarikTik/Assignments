#ifndef NODE_HPP_
#define NODE_HPP_

template<typename T>
struct node{
     node(T value, node<T> *previous = nullptr, node<T> *next = nullptr) : data(value)
     {
          link_previous(previous);
          link_next(next);
     }
     void link_previous(node<T>* previous){
          this->previous = previous;
          previous->next = this;
     }
     void link_next(node<T>* next){
          this->next = next;
          next->previous = this;
     }
     T data;
     node<T> *next = nullptr;
     node<T> *previous = nullptr;
};


#endif