#include "binary_expression.hpp"
#include <charconv>

 
template<typename LHS, typename RHS, typename Result>
Result parse_or_modify (const std::string &op, LHS lhs, RHS rhs, std::string &lhs_ref, std::string &rhs_ref){
     // if (op == "+") return numeric_val;
     // if (op == "-") return -numeric_val;
     // if (op == "*") return numeric_val * numeric_val;
     // if (op == "/") return numeric_val / numeric_val;
     // if (op == "%") return numeric_val % numeric_val;
     // if (op == "**") return std::pow(numeric_val, numeric_val);
     throw std::runtime_error("OperatorError: Invalid operator: " + op);
}
binary_expression::binary_expression(const std::string &op, const std::string &lhs, const std::string &rhs)
     : _lhs(lhs), _rhs(rhs), _op(op)
{
}

std::string binary_expression::interpret(context &cont)
{
     long lhs_integer, rhs_integer;
     double lhs_double, rhs_double;

     auto context_lhs = cont.try_get(_lhs);
     auto context_rhs = cont.try_get(_rhs);

     if (context_lhs != std::nullopt) 
          _lhs = context_lhs->get();

     if (context_rhs != std::nullopt)
          _rhs = context_rhs->get();

     auto [_i1, ec_i1] = std::from_chars(_lhs.data(), _lhs.data() + _lhs.size(), lhs_integer);

     if (ec_i1 != std::errc{}){
          auto [_d1, ec_d1] = std::from_chars(_lhs.data(), _lhs.data() + _lhs.size(), lhs_double);
          if (ec_d1 != std::errc{}) throw std::runtime_error("TokenError: Invalid token: " + _lhs);
     }

     auto [_i2, ec_i2] = std::from_chars(_rhs.data(), _rhs.data() + _rhs.size(), rhs_integer);
     if (ec_i2 != std::errc{}){
          auto [_d2, ec_d2] = std::from_chars(_rhs.data(), _rhs.data() + _rhs.size(), rhs_double);
          if (ec_d2 != std::errc{}) throw std::runtime_error("TokenError: Invalid token: " + _rhs);
     }
     return "";
     // return std::to_string(parse_or_modify(_op, lhs_integer, rhs_integer, _lhs, _rhs));
}
