#include "menu.h"
#include "menu_options.h"
#include "fio.h"
#include "../employee.h"
#include "../utilities/yes_no.h"
#include <stdlib.h>
 

extern unsigned employee_amount_limit;
extern int quit_flag; //while flag is 0 program runs

employee** employee_list;

char* stdout_format = "name: %s\nrate: $%d/hr\nhours worked: %d\n";

int list_created = 0;

void create_employee_buffer(){
    if (!list_created)
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

void save_accept_upload(){
    save_file_ask_for_location();
    save_file_create();
    save_file_download();
}

void save_decline_upload(){

}

void menu_prompt_for_save_file(){
    yes_no("do you want to download employee data from file? (yes/no)\n",
     save_accept_upload,
     save_decline_upload);
    puts("");
}

void menu_run(void){
    menu_welcome();
    menu_prompt_for_save_file();

    create_employee_buffer();
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