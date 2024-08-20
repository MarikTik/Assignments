#include "employee_info.h"
#include "global/employee_constraints.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


 

typedef struct private_employee_info {
	char* name;
	double rate;
	double hours;
} employee_info;


employee_info* employee_info_input(void) {
	employee_info* employee = (employee_info*)malloc(sizeof(employee_info));
	
	if (!employee) return NULL;

	employee->name = (char*)malloc(employee_name_limit);
	
	if (!employee->name) {
		free(employee);
		return NULL;
	}
	printf("Enter name: ");

	if (!scanf("%s", employee->name, employee_name_limit) || strcmp(employee->name, "-1") == 0)
		return employee_info_destroy(employee);

	printf("Enter hourly rate: ");

	if (!scanf("%lf", &employee->rate) || employee->rate == -1)
		return employee_info_destroy(employee);

	printf("Enter hours worked: ");

	if (!scanf("%lf", &employee->hours) || employee->hours == -1)
		return employee_info_destroy(employee);

	return employee;
}

void employee_info_print(const employee_info* employee) {
	printf("\nEmployee:\t%s\n", employee->name);
	printf("Hours worked:\t%.2lf\n", employee->hours);
	printf("Hourly rate:\t%.2lf$\n", employee->rate);
}

void* employee_info_destroy(employee_info* employee) {
	free(employee->name);
	free(employee);
	return NULL;
}

char* employee_info_get_name(employee_info* employee) {
	return employee->name;
}