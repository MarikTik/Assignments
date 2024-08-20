#include "cli.h"
#include <string.h>
#include "../global/employee_constraints.h"

void cli_arg_parse(int argc, char** argv) {
	if (argc == 2)
		employee_amount_limit = atoi(argv[1]);
}