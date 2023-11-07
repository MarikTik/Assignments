#include <iostream>
#include <fstream>
#include <iomanip>
#include "combat_details.h"

void foo(){
     size_t x;
    std::cin >> x;
    int z = 0;
    size_t arr[x];
    int y = 0; 

    for (size_t i = 0; i < x; i++){
        arr[i] = i;
    }
    std::cout << "This is interesting\n";
    std::cin >> x;
    for (size_t i = 0; i < x; i++){
        arr[i] = x-i;
    }

    std::cout <<"This is even more interesting\n";
    std::cout << z << "\t" << y;
}
int main(int argc, char** argv){
    // char* input_file_path="combat.txt", *output_file_path="report.txt";
    // if (argc == 3)
    // {
    //     input_file_path = argv[1];
    //     output_file_path = argv[2];
    // }


    // combat_details details;
    // std::ifstream in_stream(input_file_path);
    // if (!in_stream.is_open()) return EXIT_FAILURE;
    // in_stream >> details;
    // in_stream.close();

    // auto report = details.create_report();
    // std::ofstream out_stream(output_file_path);
    // out_stream << report;
    
   
    foo();
    return EXIT_SUCCESS;
}