#include "token.h"

Token::Token()
{

}

Token::Token(TokenType tt, std::string desc)
{
    this->tt = tt;
    this->desc = desc;
}
