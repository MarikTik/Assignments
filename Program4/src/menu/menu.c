#pragma once
#include "menu.h"
#include "../global/employee_constraints.h"
#include "../employee_info.h"
#include <stdio.h>
#include <stdlib.h>



typedef employee_info* employee;
typedef void(*option)();

static employee* employee_list;
static unsigned employee_index = 0;

static const char* no_emplpyees_message = "There are no employees availalble";

//Lists the names of the available employees numerically from 1
void menu_list_employees() {
	for (unsigned i = 0; i < employee_index; i++) {
		printf("%u. %s\n", i + 1, (char*)employee_info_get_name(employee_list[i]));
	}
	puts("");
}

//Returns the chosen employee placement, returns 0 upon failure
unsigned menu_choose_employee() {
	unsigned choice_index;
	menu_list_employees();
	if (!scanf("%u", &choice_index))
		return 0;
	return choice_index;
}

void menu_add_employee() {
	if (employee_index >= employee_amount_limit)
	{
		puts("Can't add more employees\n");
		return;
	}
	employee new_employee = employee_info_input();
	if(new_employee)
		employee_list[employee_index++] = new_employee;
}

void menu_print_employee() {
	if (!employee_index) {
		puts(no_emplpyees_message);
		return;
	}
	unsigned index = menu_choose_employee() - 1;
	employee_info_print(employee_list[index]);
}

void menu_print_all_employees() {
	if (!employee_index) {
		puts(no_emplpyees_message);
		return;
	}
	for (unsigned i = 0; i < employee_index; i++) {
		employee_info_print(employee_list[i]);
	}
	puts("");
}

void menu_edit_employee() {
	if (!employee_index) {
		puts(no_emplpyees_message);
		return;
	}
	unsigned index = menu_choose_employee() - 1;
	employee* target_employee = &employee_list[index];
	employee_info_destroy(*target_employee);
	*target_employee = employee_info_input();
}

void menu_quit() {
	puts("Exiting Mark's Menu app, hope you enjoyed it\n");
	exit(0);
}

char* menu_option_names[] = {
	"Add Employee",
	"Print Employee",
	"Print All Employees",
	"Edit Employee",
	"Quit"
};

option menu_options[] = {
	menu_add_employee,
	menu_print_employee,
	menu_print_all_employees,
	menu_edit_employee,
	menu_quit
};

void menu_destroy(void) {
	for (unsigned i = 0; i < employee_amount_limit; i++) {
		employee current_employee = employee_list[i];
		if (!current_employee)
			break;
		employee_info_destroy(current_employee);
	}
	free(employee_list);
}
void menu_display(void) {
	puts("\nMain Menu:\n");
	for (unsigned i = 0; i < sizeof(menu_options) / sizeof(option); i++) {
		printf("%u. %s\n\r", i + 1, menu_option_names[i]);
	}
	puts("");
}


void menu_run(void) {
	puts("WELCOME TO MARK'S MENU APPLICATION!\n");

	employee_list = (employee*)calloc(employee_amount_limit, sizeof(employee));
	unsigned option_index;
	while (1) {
		menu_display();
		
		if (scanf("%u", &option_index)) {
			puts("");
			menu_options[option_index - 1]();
		}
	}
	menu_destroy();
}