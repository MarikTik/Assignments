#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <variant>
#include "token_type.hpp"

struct token{
     using literal_t = std::variant<std::string, double>;
     token(token_type _type, std::string _lexeme, literal_t _literal, size_t _line)
          : type(_type), lexeme(_lexeme), literal(_literal), line(_line)
     {
     }
     const token_type type;
     const std::string lexeme;
     const literal_t literal;
     const size_t line;
};


#endif