// Program 1 - reverse polish expressions by Mark Tikhonov, Aug 19, 2024

#include <iostream>
#include <stdexcept>
#include <string>
#include <istream>
#include <cmath>

template <typename T>
struct node{
     node(T data, node<T> *next=nullptr): data(data), next(next)
     {
     }
     T data;
     node<T> *next;
};


template<typename T>
class stack{
     public:
          bool is_empty() const{
               return not _size;
          }
          size_t size() const{
               return _size;
          }
          void push(T item){
               auto new_node = new node<T>(item);
               new_node->next = _top;
               _top = new_node;
               _size ++;
          }
          T pop(){
               if (is_empty())
                    throw std::underflow_error("attempted to pop an element from stack, but it is empty");

               T value = _top->data;
               auto ptr = _top;
               _top = _top->next;
               delete ptr;
               _size --;
               return value;
          }
          void clear(){
               while(_size--)
               {
                    auto ptr = _top;
                    _top = _top->next;
                    delete ptr;
               }
          }
          ~stack(){
               clear();
          }    
     private:
          node<T> *_top;
          size_t _size = 0;
};


class reverse_polish_expression{
     public:
          friend std::istream &operator >> (std::istream &in, reverse_polish_expression &expression);
          double result();
     private:
          stack<double> _stack;
          double _result = 0;
};        

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

//normally I wouldn't evaluate the expression while reading, but I really didn't want to deal with streams
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


int main(){
     while (true){
          try{
               reverse_polish_expression expression; // the object shouldn't be reused, as the inner stack object may not be cleared if exception occurs
               std::cin >> expression;
               std::cout << "result = " << expression.result() << "\n";
          }
          catch(std::exception &ex){
               std::cout << ex.what() << "\n";
          }
     }
}
