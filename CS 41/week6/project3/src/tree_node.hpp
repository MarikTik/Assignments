#ifndef TREE_NODE_HPP_
#define TREE_NODE_HPP_

template<typename T>
struct tree_node{
     tree_node(T value, tree_node<T> *left = nullptr, tree_node<T> *right = nullptr)
          : value(value), left(left), right(right)
     {
     }
     T value;
     tree_node<T> *left;
     tree_node<T> *right;
};


#endif