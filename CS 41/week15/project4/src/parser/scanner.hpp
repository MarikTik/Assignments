#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "utils/token.hpp"
#include "collections/ordered_list.hpp"
class scanner{
     public:
          scanner(std::istream &source);
          const ds::ordered_list<token> tokens();
     private:
          std::istream & _source;
          ds::ordered_list<token> _tokens;

          struct state{
               std::string::const_iterator start;
               std::string::const_iterator current;
               std::string::const_iterator end;
               size_t line = 1;
          } _state;

};

#endif