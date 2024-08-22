#ifndef NODE_HPP_
#define NODE_HPP_

template<typename T>
struct node{
     node(T value) : data(value)
     {
           
     }
     T data;
     node<T> *next = nullptr;
     node<T> *previous = nullptr;
};


#endif