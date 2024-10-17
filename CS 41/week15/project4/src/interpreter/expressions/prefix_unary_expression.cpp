#include "prefix_unary_expression.hpp"
#include <charconv>
#include <system_error>

prefix_unary_expression::prefix_unary_expression(std::string &&op, std::string &&token)
     : _token(token), _op(op)
{
}


template<typename T>
T parse_and_modify (const std::string &op, T numeric_val, std::string &token_ref){
     if (op == "-") return -numeric_val;
     if (op == "+") return numeric_val;
     if (op == "++"){
          ++numeric_val;
          token_ref = std::to_string(numeric_val);
          return numeric_val;
     }
     if (op == "--"){
          --numeric_val;
          token_ref = std::to_string(numeric_val);
          return numeric_val;
     }
     throw std::runtime_error("OperatorError: Invalid operator: " + op);
}
 

std::string prefix_unary_expression::interpret(context &cont)
{
     long val_integer;
     // double val_double;
     
     // auto context_token = cont.try_get(_token);
     
     // if (context_token != std::nullopt)
     // {
     //      auto &token_ref = context_token->get();
     // } 
     // else{

     // }
     // auto [_1, ec1] = std::from_chars(_token.data(), _token.data() + _token.size(), val_integer);
     // if (ec1 == std::errc{}) return std::to_string(parse_or_modify(_op, val_integer, _token));

     // auto [_2, ec2] = std::from_chars(_token.data(), _token.data() + _token.size(), val_double);
     // if (ec2 == std::errc{}) return std::to_string(parse_or_modify(_op, val_double, _token)); 

     throw std::runtime_error("TokenError: Invalid token: " + _token);
}