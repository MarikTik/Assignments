#ifndef BORG_INTERPRETER_HPP
#define BORG_INTERPRETER_HPP
#include <istream>
#include <sstream>
#include "collections/hash_table.hpp"

hash_table<std::string, std::function<void(std::istream)>> translation_table{5};

class borg_interpreter{
     
     public:
          void interpret(std::istream &is){
               std::string line;
               while(std::getline(is, line)){
                    interpret_line(std::stringstream(line));
               }
          }
     private:
          void interpret_line(std::istream &&is){
               std::string keyword;
               is >> keyword;


               
               
          }
};
#endif