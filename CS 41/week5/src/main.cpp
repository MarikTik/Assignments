#include <iostream>
#include <string>
#include "sorted_list.hpp"
#include "person.hpp"
 
static const auto weight_comparator = [](const person &person1, const person &person2){
     return person1.weight < person2.weight;
};

static const auto name_length_comparator = [](const person &person1, const person &person2){
     return person1.name.size() < person2.name.size();
};

template <size_t persons_n = 15>
class application{
     public:

          void run(){
               for (size_t i = 0; i < persons_n; i++){
                    person person;
                    std::cin >> person;
                    _list_sorded_by_name_length.insert(person);
                    _list_sorted_by_weights.insert(person);
               }
               std::cout << "Names & weights sorted(ascending) by name. : " << _list_sorded_by_name_length;
               std::cout << "\nNames & weights sorted(ascending) by weight. : " << _list_sorted_by_weights;
          }
     private:
          sorted_list<person> _list_sorted_by_weights{weight_comparator};
          sorted_list<person> _list_sorded_by_name_length{name_length_comparator};
};


int main(){
     application app;
     app.run();
}