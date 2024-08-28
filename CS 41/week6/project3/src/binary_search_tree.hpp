#ifndef BINARY_SEARCH_TREE_HPP_
#define BINARY_SEARCH_TREE_HPP_
#include "tree_node.hpp"
#include <type_traits>
#include <functional>
#include <optional>

template<typename T>
class binary_search_tree{
     
     template<typename U>
     using visitor_f = std::function<U(tree_node<T> *)>;

     public:
          void add(T value){
               std::function<void(tree_node<T>**)> add_impl = [&](tree_node<T> **root_ptr){
                    auto *node = new tree_node<T>(value);
                    auto &root = *root_ptr;
                    if (not root) root = node;
                    else if (value < root->value) add_impl(&root->left);
                    else add_impl(&root->right); 
               };
               add_impl(&_root);
          }

          size_t height(){
               visitor_f<size_t> height_impl = [&](tree_node<T> *node){
                    if (not node) return 0lu;

                    return 1 + std::max({
                         height_impl(node->left),
                         height_impl(node->right)
                    });
               };
               return height_impl(_root);
          }

          size_t leaves(){
               visitor_f<size_t> leaves_impl = [&](tree_node<T> *node){
                    if (not node) return 0lu; 
                    if (not node->left and not node->right) return 1lu; // leaf found
                    return leaves_impl(node->left) + leaves_impl(node->right);
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
          // this function will run over the tree in search of an element that has the most extreme value of a desired property
          template<typename Predicate> 
          T find_extremality(Predicate predicate){
               static_assert(
                    std::is_invocable_r_v<bool, Predicate, const T&, const T&>, 
                    "Predicate must be invocable with (const T&, const T&) and return a boolean"
               );
               if (not _root) throw std::underflow_error("binary tree is empty");

               T extremality = _root->value;
               visitor_f<void> find_extremality_impl = [&](tree_node<T> *node){
                    if (not node) return;
                    if (predicate(node->value, extremality)) extremality = node->value;
                    find_extremality_impl(node->left);
                    find_extremality_impl(node->right);    
               };
               find_extremality_impl(_root);
               return extremality;
          }
          T minimum(){
               visitor_f<T> minimum_impl = [&](tree_node<T> *node){
                    if (node->left) return minimum_impl(node->left);                    
                    return node->value;
               };
               if (not _root) throw std::underflow_error("binary tree is empty");
               return minimum_impl(_root);
          }

          void print_preorder(std::ostream &os = std::cout){
               visitor_f<void> print_preorder_impl = [&](tree_node<T> *node){
                    if (node) {
                         os << node->value << " ";
                         print_preorder_impl(node->left);
                         print_preorder_impl(node->right);
                    }
               };
               print_preorder_impl(_root);
               os << "\n";
          }
          void print_postorder(std::ostream &os = std::cout){
               visitor_f<void> print_postorder_impl = [&](tree_node<T> *node){
                    if (node) {
                         print_postorder_impl(node->left);
                         print_postorder_impl(node->right);
                         os << node->value << " ";
                    }
               };
               print_postorder_impl(_root);
               os << "\n";
          }
          void print_inorder(std::ostream &os = std::cout){
               visitor_f<void> print_inorder_impl = [&](tree_node<T> *node){
                    if (node) {
                         print_inorder_impl(node->left);
                         os << node->value << " ";
                         print_inorder_impl(node->right);
                    }
               };
               print_inorder_impl(_root);
               os << "\n";
          }

     private:
          tree_node<T> *_root = nullptr;
};


#endif