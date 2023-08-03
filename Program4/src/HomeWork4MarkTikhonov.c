#include <stdio.h>
#include "utilities/cli.h"
#include "menu/menu.h"

int main(int argc, char* argv[]) {
	cli_arg_parse(argc, argv);
	menu_run();
}