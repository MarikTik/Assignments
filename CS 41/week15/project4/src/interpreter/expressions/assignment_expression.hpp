#ifndef ASSIGNMENT_EXPRESSION_HPP
#define ASSIGNMENT_EXPRESSION_HPP
#include "expression.hpp"

class assignment_expression : public expression{
     public:
          assignment_expression(std::string &&op, std::string &&token, std::string &&value);
          std::string interpret(context &cont) override;
     private:
          std::string _token;
          std::string _value;
          std::string _op;
};

#endif