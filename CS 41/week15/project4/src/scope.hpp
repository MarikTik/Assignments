#ifndef SCOPE_HPP
#define SCOPE_HPP
#include <string>
#include <istream>
#include "collections/hash_table.hpp"
#include "collections/list.hpp"

class scope{
     public:
          void create_variable(std::istream &is){
               std::string name, value, delimeter;
               is >> name >> delimeter >> value;
               if (not value.length()) _local_variables.emplace(name, "undefined");
               else _local_variables.emplace(name, value);
          }
          void assign_variable(std::istream &is){ // for simple assignments and math expressions
               
          }
          void manipulate_variable(std::istream &is){

          }


     private:
          string_map<std::string> _local_variables;
          list<scope> _local_scopes;
};
#endif