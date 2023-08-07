#include "menu.h"
#include "menu_options.h"
#include <stdlib.h>
#include "../employee.h"

extern unsigned employee_amount_limit;
extern int quit_flag; //while flag is 0 program runs

employee** employee_list;

char* stdout_format = "name: %s\nrate: %d\nhours worked: %d\n";

void create_employee_buffer(){
    employee_list = (employee**)calloc(employee_amount_limit, sizeof(employee*)); 
}

char* menu_option_names[] = {
    "add employee",
    "print employee",
    "edit employee",
    "print all employees",
    "quit"
};
void(*menu_options[])() = {
    menu_add,
    menu_print,
    menu_edit,
    menu_print_all,
    menu_quit
};

void menu_welcome(){
    puts("\nwelcome to Mark's application\n\n");
}
void menu_run(void){
    create_employee_buffer();
    menu_welcome();

    while(!quit_flag){
        for(int i = 0; i < sizeof(menu_options) / sizeof(menu_options[0]); i++)
            printf("%d. %s\n", i + 1, menu_option_names[i]);
        puts("");
        unsigned choice;
        scanf("%u", &choice);
        puts("");
        menu_options[choice - 1]();
        puts("");
    }
    

}