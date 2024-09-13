#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include "borg_interpreter.hpp"
#include "parser/expression_parser.hpp"

int main(int argc, char *argv[]){  


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
   
     
     expression_parser parser;
     std::string expression = "1 + 5 * 3 + 1 - 3 ** 3";
     auto stream = std::stringstream(expression);
     std:: cout << parser.parse(stream) << "\n";
 

}