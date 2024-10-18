#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

enum class token_type{
     // single-character tokens.
     LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
     COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

     // one or two character tokens.
     BANG, BANG_EQUAL,
     EQUAL, EQUAL_EQUAL,
     GREATER, GREATER_EQUAL,
     LESS, LESS_EQUAL, INCREMENT, DECREMENT,

     // Literals.
     IDENTIFIER, STRING, NUMBER,

     // Keywords.
     AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
     PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

     // End of file
     END
};

#endif