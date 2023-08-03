#pragma once

typedef struct private_employee_info employee_info;

//returns a pointer to a heap allocated variable, the lvalue owns it.
//returns NULL upon failure
employee_info* employee_info_input(void);

void employee_info_print(const employee_info*);

//frees the employee struct and returns NULL
void* employee_info_destroy(employee_info*);

//returns the name of the employee
char* employee_info_get_name(employee_info*);