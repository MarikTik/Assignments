#include "fio.h"
#include <stdio.h>

#define PATH_SIZE 100

static char path[PATH_SIZE];
 
void save_file_create(){
 FILE* stream = fopen(path, "w+");
 if (stream)
   fclose(stream);
}
 
void ask_for_save_file_location(){
 puts("Enter the path for save file");
 scanf("%s", path);
}