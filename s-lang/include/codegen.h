#ifndef CODEGEN_H
#define CODEGEN_H

#include "token.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class CodeGen
{
public:
    CodeGen();
    void create_project();
    void generate(std::vector<Token> tokens);
    void build();
    std::string code;

private:
    std::vector<Token> tokens;
};

#endif // CODEGEN_H
