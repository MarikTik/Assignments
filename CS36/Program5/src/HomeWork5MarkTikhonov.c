#include "args_parse.h"
#include "menu/menu.h"


int main(int argc, char* argv[]){
    args_parse(argc, argv);
    menu_run();
    
    return 0; 
}
 