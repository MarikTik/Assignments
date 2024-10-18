#ifndef SCOPE_HPP
#define SCOPE_HPP
#include <string>
#include <istream>
#include "collections/hash_table.hpp"
#include "collections/linked_list.hpp"
#include "collections/stack.hpp"

class scope{
     public:
          friend std::istream &operator >>(std::istream &is, scope &s){
               std::string token;
               is >> token;
               std::transform(token.begin(), token.end(), token.begin(), ::tolower);

               if (token == "var"){
                    std::string name; 
                    is >> name;
                    std::string delimeter;
                    is >> delimeter;
                    if (delimeter != "=") throw std::runtime_error("expected '=' after variable name");
                    std::string value;
                    is >> value;
                    s._local_variables.insert_or_assign(name, value);
               }
               
          }

     private:
          scope * _parent_scope = nullptr;
          ds::named_table<std::string> _local_variables;
          ds::named_table<std::string> _local_functions;

};
#endif