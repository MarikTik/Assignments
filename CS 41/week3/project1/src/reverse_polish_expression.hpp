#ifndef REVERSE_POLISH_EXPRESSION_HPP_
#define REVERSE_POLISH_EXPRESSION_HPP_
#include <string>
#include <istream>
#include "stack.hpp"

class reverse_polish_expression{
     public:
          friend std::istream &operator >> (std::istream &in, reverse_polish_expression &expression);
          double result();
     private:
          stack<double> _stack;
          double _result = 0;
};        

#endif