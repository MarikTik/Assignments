#include "postfix_unary_expression.hpp"
#include <charconv>
#include <iostream>
template<typename T>
T parse_or_modify (T numeric_val, std::string &token_ref, const std::string &op){
     
     if (op == "++"){
          token_ref = std::to_string(numeric_val + 1);
          std::cout << "token_ref = " << token_ref << std::endl;
          return numeric_val;
     }
     if (op == "--"){
          token_ref = std::to_string(numeric_val - 1);
          return numeric_val;
     }
     throw std::runtime_error("OperatorError: Invalid operator: " + op);
}

postfix_unary_expression::postfix_unary_expression(const std::string &op, const std::string &token)
     : _token(token), _op(op)
{
}

std::string postfix_unary_expression::interpret(context &cont)
{
     long val_integer;
     double val_double;
     
     auto context_token = cont.try_get(_token);

     if (context_token != std::nullopt) 
          _token = context_token->get();

     auto [_1, ec1] = std::from_chars(_token.data(), _token.data() + _token.size(), val_integer);
     if (ec1 == std::errc{}) return std::to_string(parse_or_modify(val_integer, _token, _op));

     auto [_2, ec2] = std::from_chars(_token.data(), _token.data() + _token.size(), val_double);
     if (ec2 == std::errc{}) return std::to_string(parse_or_modify(val_double, _token, _op)); 

     throw std::runtime_error("TokenError: Invalid token: " + _token);
}

 