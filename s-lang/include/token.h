#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/*enum class TokenType {
    WORD,
    LBRACE,
    RBRACE,
    EOF
};*/

enum class TokenType {
    WORD,
    STRING,
    INT,
    LBRACE,
    RBRACE,
};

class Token
{
public:
    Token();
    Token(TokenType tt, std::string desc);

    std::string tt_ts();

    TokenType tt;
    std::string desc;
};

#endif // TOKEN_H
