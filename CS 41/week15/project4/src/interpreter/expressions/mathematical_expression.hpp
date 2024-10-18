#ifndef MATHEMATICAL_EXPRESSION_HPP
#define MATHEMATICAL_EXPRESSION_HPP
#include "expression.hpp"
#include "collections/hash_set.hpp"
struct mathematical_expression : public expression{
     static ds::hash_set<std::string> operators(){
          return {"+", "-", "*", "/", "%", "**", "++", "--", "+=", "-=", "*=", "/=", "%="};
     }

};

#endif