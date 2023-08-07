#include "menu_options.h"
#include "../employee.h"

extern char* stdout_format;

extern unsigned employee_amount_limit;
extern employee** employee_list;

static size_t index = 0;
static size_t employee_choice_index;

int quit_flag;
void choose_employee(){
    for(size_t i = 0; i < index; i++)
        printf("%lu. %s\n", i + 1, employee_get_name(employee_list[i]));
    
    scanf("%lu", &employee_choice_index);
    employee_choice_index--;
}

void menu_add(void){
    if (index < employee_amount_limit - 1){
        employee_list[index++] = employee_input(); 
    }
    else puts("no free space left");
}

void menu_print(void){
    choose_employee();
    employee_print(employee_list[employee_choice_index], stdout_format);
}

void menu_print_all(void){
    employee_print_many_to_file(employee_list, index, stdout_format, stdout);
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

void menu_quit(void){
    quit_flag = 1;
}