#ifndef YES_NO_H_
#define YES_NO_H_

typedef void (*callback)();

void yes_no(const char* message, callback yes_callback, callback no_callback);

#endif