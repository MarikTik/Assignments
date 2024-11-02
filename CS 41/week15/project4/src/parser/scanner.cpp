#include "scanner.hpp"
#include "utils/error.hpp"
#include <sstream>

scanner::scanner(std::istream &source)
     : _source(source)
{
}

token next_token(std::string::const_iterator &current, const std::string::const_iterator &end, size_t line)
{
     while(current != end){
          switch(*current){
               case '(': return token(token_type::LEFT_PAREN, "(", "", line);
               case ')': return token(token_type::RIGHT_PAREN, ")", "", line);
               case '{': return token(token_type::LEFT_BRACE, "{", "", line);
               case '}': return token(token_type::RIGHT_BRACE, "}", "", line);
               case ',': return token(token_type::COMMA, ",", "", line);
               case '.': return token(token_type::DOT, ".", "", line);
               case '-': return token(token_type::MINUS, "-", "", line);
               case '+': return token(token_type::PLUS, "+", "", line);
               case ';': return token(token_type::SEMICOLON, ";", "", line);
               case '*': return token(token_type::STAR, "*", "", line);
               case '!': return token(token_type::BANG, "!", "", line);
               case '=': return token(token_type::EQUAL, "=", "", line);
               case '<': return token(token_type::LESS, "<", "", line);
               case '>': return token(token_type::GREATER, ">", "", line);
               case '/': return token(token_type::SLASH, "/", "", line);
               case ' ':
               case '\t':
               case '\n':
                    break;
               default:
                    error(line, "Unexpected character.");
          }
          current++;
     }
     return token(token_type::END, "", "", line);

}
const ds::ordered_list<token> scanner::tokens()
{
     ds::ordered_list<token> tokens;
     std::string line;
     while(std::getline(_source, line)){
          _state.start = _state.current = line.cbegin();
          _state.end = line.cend();

          while(_state.current != _state.end){
               tokens.push_back(next_token(_state.current, _state.end, _state.line));
          }
          _state.line++;
     }
     
     tokens.push_back(token(token_type::END, "", "", 0));
     return tokens;
}
