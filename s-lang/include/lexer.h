#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "token.h"

static std::map<std::string, TokenType> syms {
    {"!", TokenType::NOT},
    {"+", TokenType::PLUS},
    {"-", TokenType::MINUS},
    {"*", TokenType::STAR},
    {"/", TokenType::DIV},
    {">", TokenType::GT},
    {"<", TokenType::LT},
    {"%", TokenType::PERCENT},
    {"{", TokenType::LBRACE},
    {"}", TokenType::RBRACE},
    {"(", TokenType::LBRACEC},
    {")", TokenType::RBRACEC},
    {",", TokenType::COMMA},
    {".", TokenType::DOT},
    {";", TokenType::SEMICOLON},
    {"=", TokenType::EQ},

    {"+=", TokenType::PLUSEQ},
    {"-=", TokenType::MINUSEQ},
    {"*=", TokenType::STAREQ},
    {"/=", TokenType::DIVEQ},
    {">=", TokenType::GTEQ},
    {"<=", TokenType::LTEQ},

    {"==", TokenType::EQEQ},
    {"!=", TokenType::NOTEQ}
};

class Lexer
{
public:
    Lexer();
    Lexer(std::string code);

    std::vector<Token> tokens;
    std::string code;

private:
    int parse_word(int offset);
    int check(int offset);
    bool check_end_word(int offset, bool is_first_letter);
    int parse_string(int offset, char strsym);
    int parse_int(int offset);
    bool isdigit(int offset);
    bool issym(int offset);
};

#endif // LEXER_H
