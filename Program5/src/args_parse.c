#include "args_parse.h"
#include <stdlib.h>

unsigned employee_name_limit = 30;
unsigned employee_amount_limit = 3;

void args_parse(int argc, char* argv[]){
    if (argc > 1)
        employee_amount_limit = atoi(argv[1]);
    if (argc > 2)
        employee_name_limit = atoi(argv[2]);
}