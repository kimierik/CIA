#ifndef LEXER_H
#define LEXER_H

#include "../ulits/datastructures.c"


typedef enum TokenType{
    Identifier,

    Lparen,     //(
    Rparen,     //)

    Lsquirly,   //{
    Rsquirly,   //}

    DoubleQuote, //"
    SingleQuote, //'

    IntLiteral,
    StringLiteral,
    CharLiteral,

    Semicolon,
    Comma,
    Equals,
    Operator,

}TokenType;

//do i change this to stack?

typedef struct Token{
    TokenType type;
    char* value;
    char v; //HACK for operators
}Token;



typedef struct Lexer{
    int pos;
    struct Stack string;

}Lexer;


#endif
