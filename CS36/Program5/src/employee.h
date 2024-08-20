#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
#include <stdio.h>

typedef struct _employee employee;

employee* employee_create(char* name, int rate, int hours_worked);
employee* employee_create_empty(void);

void employee_print(employee* employee, char* format); 
void employee_print_to_file(employee* employee, char* format, FILE* stream);
void employee_print_many_to_file(employee** employees, size_t size, char* format, FILE* stream);

employee* employee_input(void);
employee* employee_input_from_file(char* format, FILE* stream);
employee** employee_input_many_from_file(char* format, FILE* stream, size_t* size);

char* employee_get_name(employee* employee);
void employee_destroy(employee* employee);

// format string has to be of the form "...%s...%d...%d..." (name, rate, hours)
                                        
#endif