#ifndef POSTFIX_UNARY_EXPRESSION
#define POSTFIX_UNARY_EXPRESSION
#include "mathematical_expression.hpp"

class postfix_unary_expression : public mathematical_expression{
     public:
          postfix_unary_expression(const std::string &op, const std::string &token);
          std::string interpret(context &context) override;
     private:
          std::string _token;
          std::string _op;
};
#endif