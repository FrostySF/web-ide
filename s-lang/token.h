#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    WORD,
    STRING,
    INT,

    PERCENT,
    PLUS,
    MINUS,
    STAR,
    DIV,
    PLUSEQ,
    MINUSEQ,
    STAREQ,
    DIVEQ,

    EQ,
    EQEQ,
    GT,
    LT,
    GTEQ,
    LTEQ,
    NOT,
    NOTEQ,

    LBRACE,
    RBRACE,
};

class Token
{
public:
    Token();
    Token(TokenType tt, std::string desc);

    TokenType tt;
    std::string desc;
};

#endif // TOKEN_H
