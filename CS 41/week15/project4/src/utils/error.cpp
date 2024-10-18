#include "error.hpp"
#include <iostream>

void error(size_t line, const std::string &message)
{
     report(line, "", message);
}

void report(size_t line, const std::string &where, const std::string &message)
{
     std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
}