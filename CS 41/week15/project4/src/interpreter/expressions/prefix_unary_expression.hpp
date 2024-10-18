#ifndef PREFIX_UNARY_EXPRESSION
#define PREFIX_UNARY_EXPRESSION
#include "expression.hpp"

class prefix_unary_expression : public expression{
     public:
          prefix_unary_expression(std::string &&op, std::string &&token);
          std::string interpret(context &cont) override;
     private:
          std::string _token;
          std::string _op;
};

#endif