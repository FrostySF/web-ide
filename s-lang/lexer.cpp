#include "lexer.h"

Lexer::Lexer()
{
    this->code = "";
    this->tokens = std::vector<Token>();
}

Lexer::Lexer(std::string code)
{
    this->code = code;
    this->tokens = std::vector<Token>();
    for (int i = 0; i < code.size(); i++) {
        i += this->check(i);
    }
}

int Lexer::check(int offset)
{
    switch (code[offset]) {
    case ' ':
        {
            return 0;
        }
    case '\n':
        {
            return 0;
        }
    case '\"':
        {
            return parse_string(offset, '\"');
        }
    case '\'':
        {
            return parse_string(offset, '\'');
        }
    }

    if (issym(offset)) {
        short r = 0;
        std::string s = std::string();
        s += code[offset];
        if (code[offset+1] == '=') {
            s += "=";
            r = 1;
        }
        this->tokens.push_back(Token(syms[s], s));
        return r;
    }

    if (!check_end_word(offset, true))
        return parse_word(offset) - 1;

    if(isdigit(offset))
        return parse_int(offset) - 1;

    return 0;
}

bool Lexer::check_end_word(int offset, bool is_first_letter)
{
    std::string l = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_";
    if (is_first_letter)
        l = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_";
    for(const auto& it : l)
    {
        if(it == code[offset])
            return false;
    }
    return true;
}

bool Lexer::isdigit(int offset)
{
    std::string l = "1234567890";
    for(const auto& it : l)
    {
        if(it == code[offset])
            return true;
    }
    return false;
}

bool Lexer::issym(int offset)
{
    std::string l = ";,.%{}()+-*/><=\'\"";
    for(const auto& it : l)
    {
        if(it == code[offset])
            return true;
    }
    return false;
}

#define NEXT()  tmpoffset++; \
                point = offset + tmpoffset;

#define CURR_C() c = code[point];

int Lexer::parse_word(int offset)
{
    int tmpoffset = 0;
    char c = '\0';
    std::string tmp = "";
    int point = offset + tmpoffset;
    while (point < code.size() && !check_end_word(point, false)) {
        CURR_C()
        tmp += c;
        NEXT()
    }

    this->tokens.push_back(Token(TokenType::WORD, tmp));
    return tmpoffset;
}

int Lexer::parse_string(int offset, char strsym)
{
    int tmpoffset = 1;
    int point = offset + tmpoffset;
    char c = CURR_C()

    std::string tmp = "";
    while (point < code.size() && c != strsym) {
        if (c == '\\') {
            NEXT()
            CURR_C()
            tmp += '\\';
            tmp += c;
            NEXT()
            CURR_C()
            continue;
        }
        tmp += c;
        NEXT()
        CURR_C()
    }

    this->tokens.push_back(Token(TokenType::STRING, tmp));
    return tmpoffset;
}

int Lexer::parse_int(int offset)
{
    int tmpoffset = 0;
    char c = '\0';
    std::string tmp = "";
    int point = offset + tmpoffset;
    while (point < code.size() && isdigit(point)) {
        CURR_C()
        tmp += c;
        NEXT()
    }

    this->tokens.push_back(Token(TokenType::INT, tmp));
    return tmpoffset;
}
