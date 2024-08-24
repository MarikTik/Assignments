#include <iostream>
#include <ostream>

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

template<typename T>
class binary_search_tree{
     public:
          void add(T value){
               _add_helper(value, &_root);
          }
          friend std::ostream &operator << (std::ostream &os, binary_search_tree<T> &tree){ // this is the Print method (just in case)
                
               _print_inorder(os, tree._root);
               return os;
          }
     private:
          static void _add_helper(T value, tree_node<T> **root_ptr){
               auto *node = new tree_node<T>(value);
               auto &root = *root_ptr;
               if (not root)
                    root = node;

               else if (value < root->value)
                    _add_helper(value, &root->left);

               else _add_helper(value, &root->right); 
          }
          static void _print_inorder(std::ostream &os, tree_node<T> *node){
               if (node) {
                    _print_inorder(os, node->left);
                     os << node->value << " ";
                    _print_inorder(os, node->right);
               }
          }
          tree_node<T> *_root = nullptr;
};

int main(){
     binary_search_tree<int> tree;
     for (int i = 10; i >= 0; i--)
          tree.add(i);
     std::cout << tree;
}