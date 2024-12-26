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

int Lexer::check(int offset) {
    switch (code[offset]) {
    case ' ':
        {
            return 0;
        }
    case '\n':
        {
            return 0;
        }
    case '{':
        {
            this->tokens.push_back(Token(TokenType::LBRACE, "{"));
            return 0;
        }
    case '}':
        {
            this->tokens.push_back(Token(TokenType::RBRACE, "}"));
            return 0;
        }
    default:
        {
            if (!check_end_word(offset, true))
                return parse_word(offset) - 1;
            return 0;
        }
    }
}

bool Lexer::check_end_word(int offset, bool is_first_letter) {
    std::string l = "qwertyuiopasdfghjklzxcvbnm1234567890_";
    if (is_first_letter)
        l = "qwertyuiopasdfghjklzxcvbnm_";
    for(const auto& it : l)
    {
        if(it == code[offset])
            return false;
    }
    return true;
}

int Lexer::parse_word(int offset) {
    int tmpoffset = 0;
    char c = '\0';
    std::string tmp = "";
    int point = offset + tmpoffset;
    while (!check_end_word(point, false) && point < code.size()) {
        c = code[point];
        tmp += c;
        tmpoffset++;
        point = offset + tmpoffset;
    }

    this->tokens.push_back(Token(TokenType::WORD, tmp));
    return tmpoffset;
}
