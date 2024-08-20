#include "yes_no.h"
#include <string.h>
#include <stdio.h>

void yes_no(const char* message, callback yes_callback, callback no_callback){
    puts(message);
    char buffer[10];
    scanf("%s", buffer);

    if (strcmp(buffer, "yes") == 0) yes_callback();
    else if (strcmp(buffer, "no") == 0) no_callback();
    else yes_no(message, yes_callback, no_callback);
}

