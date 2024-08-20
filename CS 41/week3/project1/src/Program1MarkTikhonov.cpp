#include <iostream>
#include <fstream>
#include "reverse_polish_expression.hpp"

int main(){
     
     
     while (true){
          try{
               reverse_polish_expression expression; // the object shouldn't be reused, as the stack may not be cleared if exception occurs
               std::cin >> expression;
               std::cout << "result = " << expression.result() << "\n";
          }
          catch(std::exception &ex){
               std::cout << ex.what() << "\n";
          }
          
     }
    
}

// 10 0 / =
// 10 20 * / = Error: Too many operators
// 12 20 30 / = Error: Too many operands