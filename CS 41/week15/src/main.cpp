#include <iostream>
#include <fstream>

class borg_interpreter{
     public:
          friend std::istream& operator >> (std::istream& is, borg_interpreter& interpreter){

               return is;
          }
};
int main(int argc, char *argv[]){
     if (argc != 2){
          std::cout << "usage: ./borg <path>";
          return EXIT_FAILURE;
     }
     std::ifstream ifs(argv[1]);
     borg_interpreter interpreter;
     
}