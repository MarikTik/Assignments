#ifndef ERROR_HPP
#define ERROR_HPP
#include <string>
void error(size_t line, const std::string &message);
void report(size_t line, const std::string &where, const std::string &message);
#endif
