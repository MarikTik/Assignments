#ifndef BINARY_EXPESSION_HPP
#define BINARY_EXPESSION_HPP
#include "expression.hpp"

class binary_expression : public expression{
     public:
          binary_expression(const std::string &op, const std::string &lhs, const std::string &rhs);
          std::string interpret(context &cont) override;
     private:
          std::string _lhs;
          std::string _rhs;
          std::string _op;
};
#endif