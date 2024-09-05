#include <iostream>
#include <string>
#include "sorted_list.hpp"

class application{
     public:
          void run(size_t persons_n){
               for (size_t i = 0; i < persons_n; i++){
                    std::string name;
                    double weight;
                    std::cin >> name >> weight;
                    _list.insert(name, weight);
               }
               std::cout << "Names & weights sorted(ascending) by name. : ";
               _list.print_first_order();

               std::cout << "\nNames & weights sorted(ascending) by weight. : ";
               _list.print_second_order();
               std::cout << std::endl;
          }
     private:
          sorted_list<std::string, double> _list{
               std::less<const std::string &>{},
               std::less<double >{}
          };
};
 
int main(){
     application app;
     app.run(15);
}