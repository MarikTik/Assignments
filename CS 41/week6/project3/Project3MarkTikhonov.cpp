#include <iostream>
#include <string>
#include <type_traits>
#include <functional>
#include <optional>

struct person{
     std::string name;
     float weight;
     
     bool operator < (const person &other){
          return name < other.name;
     }
     friend std::ostream &operator << (std::ostream &os, const person &p){
          os << "{" << p.name << ", " << p.weight << "}"; 
          return os;
     }
     friend std::istream &operator >> (std::istream &is, person &p){
          is >> p.name >> p.weight;
          return is;
     }
};


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


class application{
     public:
          void run(size_t persons_n){
               for (size_t i = 0; i < persons_n; i++){
                    person new_person;
                    std::cin >> new_person;
                    _tree.add(new_person);
               }
               _tree.print_preorder();
               _tree.print_inorder();
               _tree.print_postorder();

               std::cout << "\ntree height = " << _tree.height();
               std::cout << "\nleaves amount = " << _tree.leaves();

               std::cout << "\n\nenter a name to look for: ";
               std::string name;
               std::cin >> name;

               auto query = _tree.find_if(
                    [&name](const person &p){
                         return p.name == name;
                    }
               );

               if (query.has_value()){
                    person found_person = *query;
                    std::cout << name << " weights " << found_person.weight << " lbs";
               }
               else std::cout << "no match exists";
               
               person lowest_weight_person = _tree.find_extremality(
                    [](const person &p1, const person &p2){
                         return p1.weight < p2.weight;
                    }
               );

               std::cout << "\n\nlowest weight contained in the tree: " << lowest_weight_person.weight 
                         << " lbs (belonging to " << lowest_weight_person.name << ")";

               std::cout << "\n\nfirst name in alphabetical order is " << _tree.minimum().name;  
          }
     private:
          binary_search_tree<person> _tree;
};

int main(){
     application app;
     app.run(15);
}