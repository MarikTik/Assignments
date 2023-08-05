#include "args_parse.h"
#include "employee.h"

char* save_path = "/home/mark/Desktop/Projects/Assignments/CS36_2023/Program5v2/save.txt";
char* json_format = "{\n\tName: %s,\n\tRate: %d,\n\tWork_Hours: %d,\n}";

const char* simple_format = "%s %d %d";

char* format;
int main(int argc, char* argv[]){
    format = simple_format;
    args_parse(argc, argv);
    
    FILE* stream = fopen(save_path, "r");

    // {
    //     employee* employees[] = {
    //        employee_create("Bob", 50, 40),
    //         employee_create("Mark", 100, 40),
    //         employee_create("Gleb", 70, 30),
    //         employee_create("Pound", 42, 100),
    //         employee_create("John", 550, 30)
    //     };
    //     employee_print_many_to_file(employees, 5, format, stream); 
    // }
 

    size_t size;
    employee** employees = employee_input_many_from_file(format, stream, &size);
    employee_print_many_to_file(employees, size, format, stdout);
    fclose(stream);
  
    return 0;
 
    
}
//HomeWork5MarkTikhonov.c 