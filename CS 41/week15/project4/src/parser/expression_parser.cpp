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

static string_map<algebric_operator_t> algebric_operators {
    {"+", [](double a, double b) {return a + b;}},
    {"-", [](double a, double b) {return a - b;}},
    {"*", [](double a, double b) {return a * b;}},
    {"/", [](double a, double b) {return a / b;}},
    {"%", [](double a, double b) {return std::fmod(a, b);}},
    {"**", [](double a, double b) {return std::pow(a, b);}}
};


// I will save these till the best days
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
//

std::string expression_parser::parse(std::istream &is)
{
    stack<double> operands;
    stack<std::string> operators;
    std::string token;
    while(is >> token and not is.fail()){
        char *numeric_token_flag;
        auto value = std::strtod(token.c_str(), &numeric_token_flag);
        bool is_numeric = not *numeric_token_flag;

        if (is_numeric) 
            operands.push(value);

        else if (algebric_operators.contains(token))
        {
            if (operators.is_empty())
                operators.push(token);

            else{
           
                const auto &previous_operator = operators.peek();
                const auto &current_operator = token;
                auto previous_precedence = operator_precedence.at(previous_operator);
                auto current_precedence = operator_precedence.at(current_operator);

                if (previous_precedence >= current_precedence){
                    operators.pop();  // clean the latest operator
                    operators.push(current_operator);

                    auto right_operand = operands.pop();
                    auto left_operand = operands.pop();

                    auto result = algebric_operators.at(previous_operator)(left_operand, right_operand);
                    operands.push(result);
                }
                else operators.push(current_operator);
            }
        }
        else throw std::invalid_argument("inavlid operator " + token);
    }

    while(not operators.is_empty()){ // cleaning the rest
        auto current_operator = operators.pop();
        auto right_operand = operands.pop();
        auto left_operand = operands.pop();
        auto result = algebric_operators.at(current_operator)(left_operand, right_operand);
        operands.push(result);
    }
    return std::to_string(operands.pop());
}