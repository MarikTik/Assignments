#ifndef FIO_H_
#define FIO_H_
#include "../employee.h"

//in case the user entered a non existant file location the function will create it automatically.
void save_file_create();

// this function has to be called in the beginning before upload or in the end before save.
void  save_file_ask_for_location();

void save_file_download();

void save_file_upload();


#endif