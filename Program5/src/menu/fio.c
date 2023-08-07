#include "fio.h"
#include <stdio.h>
#include <stdlib.h>

#define PATH_SIZE 100
 
static char path[PATH_SIZE];
FILE* stream;
char* file_format = "%s %d %d";

extern employee** employee_list;
extern size_t employee_index;
extern int list_created;
extern unsigned employee_amount_limit;



void save_file_create(){
 stream = fopen(path, "ab+");
 if (stream)
   fclose(stream);
  else puts("invalid file location");
}
 
void save_file_ask_for_location(){
 puts("Enter the path for save file:\n");
 scanf("%s", path);
}

void save_file_download(){
  stream = fopen(path, "r");
  employee_list = employee_input_many_from_file(file_format, stream, &employee_index);
  list_created = 1;
  fclose(stream);
}

void save_file_upload(){
  stream = fopen(path, "w");
  employee_print_many_to_file(employee_list, employee_index, file_format, stream);
  fclose(stream);
}