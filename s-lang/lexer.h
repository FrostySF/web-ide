#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "token.h"

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
};

#endif // LEXER_H
