#include "assignment_expression.hpp"
#include "hash_table.hpp"
#include "binary_expression.hpp"
#include "hash_set"
assignment_expression::assignment_expression(std::string &&op, std::string &&token, std::string &&value)
     : _token(token), _value(value), _op(op)
{
}

std::string assignment_expression::interpret(context &cont)
{
     auto &token_ref = cont.get(_token);

     if (_op == "=") token_ref = _value;
     auto interpret = [&cont, &token_ref, this](const std::string &op){
          return binary_expression(op, token_ref, _value).interpret(cont);
     };
     token_ref = interpret(_op.substr(0, _op.size() - 1));
     return token_ref;
}
