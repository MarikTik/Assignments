#ifndef INVALID_INPUT_H_
#define INVALID_INPUT_H_
#include <exception>
#include <string>
#include <iostream>
class InvalidInput : public std::exception{
     public:
          InvalidInput(const std::string& input)
               : _message("Invalid input \"" + input + "\".\n")
          {
          }
          void reason(){
               std::cout << _message << std::endl;
          }
     private:
          const std::string _message;
};
    //implementing functions in .h file as set in the requirements

#endif