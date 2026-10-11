#ifndef LEXER_H
#define LEXER_H

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_LEXEME 100

typedef enum{
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    OPERATOR,
    SPECIAL_SYMBOL,
    STRING,
    CHARACTER,
    PREPROCESSOR,
    HEADER,
    UNKNOWN,
}TokenType;
typedef struct{
    TokenType type;
    char LEXEME[MAX_LEXEME];
}Token;
void analyze_file(FILE *fp);
const char *get_token_name(TokenType type);

#endif