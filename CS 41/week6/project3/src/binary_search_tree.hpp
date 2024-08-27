#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_
#include "tree_node.hpp"
#include <type_traits>
#include <functional>
#include <optional>

template<typename T>
class binary_search_tree{
     public:
          void add(T value){
               const auto add_impl = [&](T value, tree_node<T> **root_ptr){
                    auto *node = new tree_node<T>(value);
                    auto &root = *root_ptr;
                    if (not root)
                         root = node;

                    else if (value < root->value)
                         add_impl(value, &root->left);

                    else add_impl(value, &root->right); 
               };
               add_impl(value, &_root);
          }

          size_t height(){
               const auto height_impl = [&](tree_node<T> *node){
                    const auto *left = node->left, *right = node->right;

                    if (left and right) return 1 + std::max(height_impl(left), height_impl(right));

                    if (left) return 1 + height_impl(left);

                    if (right) return 1 + height_impl(right);

                    return 0; // leaf found
               };
               return height_impl(_root);
          }

          size_t leaves(){
               const auto leaves_impl = [&](tree_node<T> *node){
                    const auto *left = node->left, *right = node->right;

                    if (left and right) return leaves_impl(left) + leaves_impl(right);

                    if (left) return leaves_impl(left);

                    if (right) return leaves_impl(right);

                    return 1; // leaf found
               };
               return leaves_impl(_root);
          }

          template<typename Predicate>
          std::optional<std::enable_if_t<std::is_invocable_r_v<bool, Predicate, T>, T>>
          find_if(Predicate predicate){ 
               const auto find_impl = [&](const tree_node<T>* node, Predicate predicate){

                    if (not node) return std::nullopt;

                    const auto value = node->value;

                    if (std::invoke(predicate, value)) return value;

                    const auto left_find = find_impl(node->left, predicate);
                    if (left_find not_eq std::nullopt) return left_find;

                    const auto right_find = find_impl(node->right, predicate);
                    if (right_find not_eq std::nullopt) return right_find;

                    return std::nullopt;
               };
               return find_impl(_root, predicate);
          }
          void print_preorder(std::ostream &os){
               const auto print_preorder_impl = [&](std::ostream &os, tree_node<T> *node){
                    if (node) {
                         os << node->value << " ";
                         print_preorder_impl(os, node->left);
                         print_preorder_impl(os, node->right);
                    }
               };
               print_preorder_impl(os, _root);
          }
          void print_postorder(std::ostream &os){
               const auto print_postorder_impl = [&](std::ostream &os, tree_node<T> *node){
                    if (node) {
                         print_postorder_impl(os, node->left);
                         print_postorder_impl(os, node->right);
                         os << node->value << " ";
                    }
               };
               print_postorder_impl(os, _root);
          }
          void print_inorder(std::ostream &os){
               const auto print_inorder_impl = [&](std::ostream &os, tree_node<T> *node){
                    if (node) {
                         print_inorder_impl(os, node->left);
                         os << node->value << " ";
                         print_inorder_impl(os, node->right);
                    }
               };
               print_inorder_impl(os, _root);
          }
     private:
          tree_node<T> *_root = nullptr;
};


#endif