#ifndef BORG_INTERPRETER_HPP
#define BORG_INTERPRETER_HPP
#include <istream>
#include "hash_table.hpp"
class borg_interpreter{
     public:
          friend std::istream& operator >> (std::istream& is, borg_interpreter& interpreter){

               return is;
          }
          void run(){

          }
};
#endif