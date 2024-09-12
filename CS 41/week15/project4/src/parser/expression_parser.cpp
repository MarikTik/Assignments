#include "expression_parser.hpp"
#include "../collections/stack.hpp"
#include "../collections/hash_table.hpp"
#include <functional>
#include <cmath>

 
using algebric_operator_t = std::function<double(double, double)>;
using comparison_operator_t = std::function<bool(double, double)>;
using logical_opeartor_t = std::function<bool (bool, bool)>;

static string_map<uint8_t> operator_precedence{
    {"||", 1},
    {"&&", 2},
    {"<", 3},
    {">", 3},
    {"<=", 3},
    {">=", 3},
    {"==", 4},
    {"!=", 4},
    {"+", 5},
    {"-", 5},
    {"*", 6},
    {"/", 6},
    {"%", 6},
    {"**", 7}
};

static string_map<algebric_operator_t> algebric_opererators {
    {"+", [](double a, double b) {return a + b;}},
    {"-", [](double a, double b) {return a - b;}},
    {"*", [](double a, double b) {return a * b;}},
    {"/", [](double a, double b) {return a / b;}},
    {"%", [](double a, double b) {return std::fmod(a, b);}},
    {"**", [](double a, double b) {return std::pow(a, b);}}
};

static string_map<logical_opeartor_t> logical_opererators {
    {"||", [](bool a, bool b) {return a || b;}},
    {"&&", [](bool a, bool b) {return a && b;}}
};

static string_map<comparison_operator_t> comparison_operators {
    {"<", [](double a, double b) {return a < b;}},
    {">", [](double a, double b) {return a > b;}},
    {"<=", [](double a, double b) {return a <= b;}},
    {">=", [](double a, double b) {return a >= b;}},
    {"==", [](double a, double b) {return a == b;}},
    {"!=", [](double a, double b) {return a != b;}},
};

std::string expression_parser::parse(std::istream &is)
{
    stack<double> operands;
    stack<std::string> operators;
    std::string token;

    while(is >> token){
        char *numeric_token_flag;
        auto value = std::strtod(token.c_str(), &numeric_token_flag);
        bool is_numeric = *numeric_token_flag;

        if (is_numeric){
            if (operands.size() < 2) operands.push(value);
            

        }
        else{
            if (operators.is_empty()) operators.push(token);
            // else if (algebric_opererators.contains(token) or )
             
        }
    }
    return "";
}