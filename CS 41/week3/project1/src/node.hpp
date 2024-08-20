#ifndef NODE_HPP_
#define NODE_HPP_

template <typename T>
struct node{
     node(T data, node<T> *next=nullptr): data(data), next(next)
     {
     }
     T data;
     node<T> *next;
};

#endif