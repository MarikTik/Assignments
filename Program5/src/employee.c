#include "employee.h"
#include <stdlib.h>
#include <string.h>

extern unsigned employee_name_limit;
extern unsigned employee_amount_limit;

typedef struct _employee {
    char* name;
    int hours_worked;
    int rate;
} employee;

employee* employee_create(char* name, int rate, int hours_worked){
    employee* new_employee = (employee*)malloc(sizeof(employee));
    new_employee->name = name;
    new_employee->rate = rate;
    new_employee->hours_worked = hours_worked;
    return new_employee;
}
employee* employee_create_empty(void){
    return employee_create(
        (char*)(malloc(employee_name_limit)),
        0,
        0
    );
}

void employee_print(employee* employee, char* format){
    if (employee)
        employee_print_to_file(employee, format, stdout);
}

void employee_print_to_file(employee* employee, char* format, FILE* stream){
    if (employee){
        fprintf(stream, format, employee->name, employee->rate, employee->hours_worked);
        fputs("\n", stream);
    }
}

void employee_print_many_to_file(employee** employees, size_t size, char* format, FILE* stream){
    for(size_t i = 0; i < size; i++)
        employee_print_to_file(employees[i], format, stream);
}


employee* employee_input(void){
    char* name = (char*)malloc(employee_name_limit);
    int rate, hours;

    printf("Enter name: ");
    if (scanf("%s", name) != 1 || strcmp(name, "-1") == 0) return NULL;
    printf("Enter hourly rate: ");
    if (scanf("%d", &rate) != 1 || rate == -1) return NULL;
    printf("Enter hours worked: ");
    if (scanf("%d", &hours) != 1 || hours == -1) return NULL;

    return employee_create(name, rate, hours);
}

employee* employee_input_from_file(char* format, FILE* stream){
    char* name = (char*)malloc(employee_name_limit);
    int rate, hours;

    if (feof(stream) || fscanf(stream, format, name, &rate, &hours) != 3) // fscanf is not scanning well
        return NULL;
        
    fscanf(stream, "\n");
    return employee_create(name, rate, hours);
}

 
employee** employee_input_many_from_file(char* format, FILE* stream, size_t* size){
    employee** employee_list = (employee**)calloc(employee_amount_limit, sizeof(employee*));
    size_t index = 0;
    
    employee* new_employee = employee_input_from_file(format, stream);
    
    while(new_employee){
        employee_list[index++] = new_employee;
        new_employee = employee_input_from_file(format, stream);
    }
    *size = index; 
    return employee_list; 
}

char* employee_get_name(employee* employee){
    return employee->name;
}
void employee_destroy(employee* employee){
    free(employee->name);
    free(employee);
}

