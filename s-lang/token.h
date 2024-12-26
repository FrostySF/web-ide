#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/*enum class TokenType {
    WORD,
    LBRACE,
    RBRACE,
    EOF
};*/

enum class TokenType {WORD, LBRACE, RBRACE};

/*static const char *tokens[] = {
    [LBRACE] = "{",
    [RBRACE] = "}",
    [EOF] = "\0"
};*/

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
