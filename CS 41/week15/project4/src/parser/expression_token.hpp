#ifndef EXPRESSION_TOKEN_HPP
#define EXPRESSION_TOKEN_HPP
#include <string>
#include <variant>
#include <istream>
#include <sstream>
#include <type_traits>

class expression_token{
     using token_variant_t = std::variant<std::string, double, long>;

     enum token_t {
               FLOAT_OPERAND,
               INTEGER_OPERAND,
               OPERATOR
     };
     public:
          const token_variant_t& get() const{
               return _variants;
          }
          token_t type() const{
               return _type;
          }
          // template<typename T>
          // void set(T && value){
          //      if (constexpr )
          //      _variants.emplace<T>(std::forward<T>(value));
          // }

     private:
          token_variant_t _variants;
          token_t _type;
};

#endif