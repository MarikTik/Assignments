#include "args_parse.h"
#include "menu/menu.h"

char* save_path = "/home/mark/Desktop/Projects/Assignments/CS36_2023/Program5v2/save.txt";
 
 
#include "employee.h"

int main(int argc, char* argv[]){
    args_parse(argc, argv);
    menu_run();
    
    return 0; 
}
 