#include <iostream>
#include "binary_search_tree.hpp"
#include "person.hpp"

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