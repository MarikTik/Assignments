#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_
#include "tree_node.hpp"
#include <type_traits>
#include <functional>
#include <optional>

template<typename T>
class binary_search_tree{
     using printer_f = std::function<void(std::ostream&, tree_node<T> *)>;

     template<typename U>
     using visitor_f = std::function<U(tree_node<T> *)>;

     public:
          void add(T value){
               std::function<void(T, tree_node<T>**)> add_impl = [&](T value, tree_node<T> **root_ptr){
                    auto *node = new tree_node<T>(value);
                    auto &root = *root_ptr;
                    if (not root) root = node;
                    else if (value < root->value) add_impl(value, &root->left);
                    else add_impl(value, &root->right); 
               };
               add_impl(value, &_root);
          }

          size_t height(){
               visitor_f<size_t> height_impl = [&](tree_node<T> *node){
                    auto *left = node->left, *right = node->right;
                    if (left and right) return 1 + std::max({height_impl(left), height_impl(right)});
                    if (left) return 1 + height_impl(left);
                    if (right) return 1 + height_impl(right);
                    return 0lu; // leaf found
               };
               return height_impl(_root);
          }

          size_t leaves(){
               visitor_f<size_t> leaves_impl = [&](tree_node<T> *node){
                    auto *left = node->left, *right = node->right;
                    if (left and right) return leaves_impl(left) + leaves_impl(right);
                    if (left) return leaves_impl(left);
                    if (right) return leaves_impl(right);
                    return 1lu; // leaf found
               };
               return leaves_impl(_root);
          }

          template<typename Predicate>
          std::optional<T> find_if(Predicate predicate){ 
               static_assert(
                    std::is_invocable_r_v<bool, Predicate, const T&>, 
                    "Predicate must be invocable with const T& and return a boolean"
               );
               visitor_f<std::optional<T>> find_impl = [&](tree_node<T>* node) 
                    -> std::optional<T> {

                    if (not node) return std::nullopt;

                    const auto& value = node->value;
                    if (std::invoke(predicate, value)) return value;

                    const auto left_find = find_impl(node->left);
                    if (left_find) return left_find;

                    const auto right_find = find_impl(node->right);
                    if (right_find) return right_find;

                    return std::nullopt;
               };
               return find_impl(_root);
          }

          template<typename Predicate>
          T custom_minimum(Predicate predicate){
               static_assert(
                    std::is_invocable_r_v<bool, Predicate, const T&, const T&>, 
                    "Predicate must be invocable with (const T&, const T&) and return a boolean"
               );
               if (not _root) throw std::underflow_error("binary tree is empty");

               T minimum = _root->value;

               visitor_f<void> custom_minimum = [&](tree_node<T> *node){
                    if (not node) return;
                    if (predicate(node->value, minimum)) minimum = node->value;
                    custom_minimum(node->left);
                    custom_minimum(node->right); // forced to search all the tree for custom minimums      
               };
               custom_minimum(_root);
               return minimum;
          }
          T minimum(){
               visitor_f<T> minimum_impl = [&](tree_node<T> *node){
                    if (node->left) return minimum_impl(node->left);                    
                    return node->value;
               };
               if (not _root) throw std::underflow_error("binary tree is empty");
               return minimum_impl(_root);
          }

          void print_preorder(std::ostream &os){
               printer_f print_preorder_impl = [&](std::ostream &os, tree_node<T> *node){
                    if (node) {
                         os << node->value << " ";
                         print_preorder_impl(os, node->left);
                         print_preorder_impl(os, node->right);
                    }
               };
               print_preorder_impl(os, _root);
               os << "\n";
          }
          void print_postorder(std::ostream &os){
               printer_f print_postorder_impl = [&](std::ostream &os, tree_node<T> *node){
                    if (node) {
                         print_postorder_impl(os, node->left);
                         print_postorder_impl(os, node->right);
                         os << node->value << " ";
                    }
               };
               print_postorder_impl(os, _root);
               os << "\n";
          }
          void print_inorder(std::ostream &os){
               printer_f print_inorder_impl = [&](std::ostream &os, tree_node<T> *node){
                    if (node) {
                         print_inorder_impl(os, node->left);
                         os << node->value << " ";
                         print_inorder_impl(os, node->right);
                    }
               };
               print_inorder_impl(os, _root);
               os << "\n";
          }

     private:
          tree_node<T> *_root = nullptr;
};


#endif