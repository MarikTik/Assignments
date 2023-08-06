#ifndef FIO_H_
#define FIO_H_
 
//in case the user entered a non existant file location the function will create it automatically.
void save_file_create();

// this function has to be called in the beginning before upload or in the end before save.
void ask_for_save_file_location();




#endif