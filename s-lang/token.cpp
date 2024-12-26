#include "token.h"

Token::Token()
{

}

Token::Token(TokenType tt, std::string desc)
{
    this->tt = tt;
    this->desc = desc;
}

std::string Token::tt_ts()
{
    switch (this->tt) {
    case TokenType::LBRACE:
        return "LBRACE";
    case TokenType::RBRACE:
        return "RBRACE";
    case TokenType::WORD:
        return "WORD";
    case TokenType::STRING:
        return "STRING";
    case TokenType::INT:
        return "INT";
    default:
        return "NONE";
    }
}
