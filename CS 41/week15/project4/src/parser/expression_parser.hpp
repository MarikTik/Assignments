#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP
#include <string>
#include <istream>


struct expression_parser{
     std::string parse(std::istream &is); 
};

#endif