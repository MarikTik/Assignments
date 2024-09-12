#include <iostream>
#include <fstream>
#include "borg_interpreter.hpp"
#include "parser/expression_parser.hpp"
int main(int argc, char *argv[]){  
     if (argc != 2){
          std::cout << "usage: ./borg <path>\n";
          return EXIT_FAILURE;
     }
     std::ifstream borg_stream(argv[1]);
     if (not borg_stream.is_open()){
          std::cerr << "error: unable to open file " << argv[1] << "\n";
          return EXIT_FAILURE;
     }
     borg_interpreter interpreter;
     interpreter.interpret(borg_stream);
     
    
}