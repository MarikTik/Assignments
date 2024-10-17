#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include <string>
#include "context.hpp"

struct expression{
     virtual std::string interpret(context &cont) = 0; 
     virtual ~expression() = default;
};

#endif