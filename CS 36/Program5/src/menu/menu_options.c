#include "menu_options.h"
#include "fio.h"
#include "../employee.h"
#include "../utilities/yes_no.h"

extern char* stdout_format;

extern unsigned employee_amount_limit;
extern employee** employee_list;

size_t employee_index = 0;
size_t employee_choice_index;

int quit_flag;

void choose_employee(){
    for(size_t i = 0; i < employee_index; i++)
        printf("%lu. %s\n", i + 1, employee_get_name(employee_list[i]));
    
    scanf("%lu", &employee_choice_index);
    employee_choice_index--;
}

void menu_add(void){
    if (employee_index < employee_amount_limit - 1){
        employee_list[employee_index++] = employee_input(); 
    }
    else puts("no free space left");
}

void menu_print(void){
    choose_employee();
    employee_print(employee_list[employee_choice_index], stdout_format);
}

void menu_print_all(void){
    employee_print_many_to_file(employee_list, employee_index, stdout_format, stdout);
}

void menu_edit(void){
    choose_employee();
    employee** employee_ptr = &employee_list[employee_choice_index];
    employee* new_employee = employee_input();

    if(new_employee){
        employee_destroy(*employee_ptr);
        *employee_ptr = new_employee;
    }
}

void menu_accept_upload(){
    puts("");
    save_file_ask_for_location();
    save_file_create();
    save_file_upload();
    
}
void menu_decline_upload(){

}

void menu_quit(void){
    yes_no("\ndo you want to save employee data to file? (yes/no)\n",
        menu_accept_upload,
        menu_decline_upload);
    
    for (size_t i = 0; i < employee_index; i++)
        employee_destroy(employee_list[i]);
    free(employee_list);

    quit_flag = 1;
}