#ifndef FIO_H_
#define FIO_H_
#include <stdio.h>
#define PATH_SIZE 100

static char path[PATH_SIZE];
//in case the user entered a non existant file location the function will create it automatically.
void save_file_create(){
 FILE* stream = fopen(path, "w+");
 if (stream)
   fclose(stream);
}

// this function has to be called in the beginning before upload or in the end before save.
void ask_for_save_file_location(){
 puts("Enter the path for save file");
 scanf("%s", path);
}




#endif