#include <iostream>
#include <fstream>
#include "borg_interpreter.hpp"
 
int main(int argc, char *argv[]){  
     if (argc != 2){
          std::cout << "usage: ./borg <path>";
          return EXIT_FAILURE;
     }
     std::ifstream borg_stream(argv[1]);
     borg_interpreter interpreter;
     borg_stream >> interpreter;
     interpreter.run();
}