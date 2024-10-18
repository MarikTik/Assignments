// inspired by https://craftinginterpreters.com

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include "borg_interpreter.hpp"
#include "parser/expression_parser.hpp"
#include "parser/expression_token.hpp"
#include <variant>
#include "interpreter/context.hpp"
#include "interpreter/expressions/expressions.hpp"
#include <fstream>
 
//int argc [[maybe_unused]], char *argv[]
int main(){ 
     std::cerr << "Hello, World!" << std::endl;
     
     // context cont;
     // cont.add("chad", "100");
     // expression * ex = new prefix_unary_expression("++", "chad");
     // std::cout << "ex = " << ex->interpret(cont) << std::endl;
     // std::cout << cont.get("chad") << std::endl;
//      using algebric_operator_t = std::function<double(double, double)>;
// using comparison_operator_t = std::function<bool(double, double)>;
// using logical_opeartor_t = std::function<bool (bool, bool)>;

// static string_map<uint8_t> operator_precedence{
//     {"||", 1},
//     {"&&", 2},
//     {"<", 3},
//     {">", 3},
//     {"<=", 3},
//     {">=", 3},
//     {"==", 4},
//     {"!=", 4},
//     {"+", 5},
//     {"-", 5},
//     {"*", 6},
//     {"/", 6},
//     {"%", 6},
//     {"**", 7}
// };
   
      
     

     // std::variant<std::string, double> var = 5.1;
     // std::cout << std::get<double>(var) << std::endl;


}