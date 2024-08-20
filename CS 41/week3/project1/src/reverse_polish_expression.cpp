#include "reverse_polish_expression.hpp"
#include <stdexcept>
#include <stdlib.h>
#include <cmath>
// works only only with binary operations
double evaluate_binary_expression(double operand1, double operand2, std::string operation)
{

     if (operation == "+")
          return operand1 + operand2;
     if (operation == "-")
          return operand1 - operand2;
     if (operation == "*")
          return operand1 * operand2;
     if (operation == "/"){
          return operand1 / operand2;
     } 
     throw std::invalid_argument("invalid operation");
}

double reverse_polish_expression::result()
{
     return _result;
}


std::istream &operator>>(std::istream &in, reverse_polish_expression &expression)
{
     static const std::string termination_token = "=";
     std::string token;
     auto& stack = expression._stack;
     auto& result = expression._result;

     while (true){
          in >> token;

          if (token == termination_token)
               break;
          
          char* numeric_conversion_fail_flag;
          double number = std::strtod(token.c_str(), &numeric_conversion_fail_flag);

          if (*numeric_conversion_fail_flag) // conversion failed i.e. token is operator
          {
               if (stack.size() < 2)
                    throw std::logic_error("Error: Too many operators");

               double operand2 = stack.pop();
               double operand1 = stack.pop();
               stack.push(evaluate_binary_expression(operand1, operand2, token));
          }
               
          else{ // token is numeric value
              stack.push(number);
          }
     }
     result = stack.pop(); // taking the remaining value

     if (not stack.is_empty()) // operand left in stack
          throw std::logic_error("Error: Too many operands");

     if (std::isinf(result))
          throw std::runtime_error("Error: Division by zero");
     
     if (std::isnan(result))
          throw std::runtime_error("Error: forbidden application of math operations");
          
     return in;
}
