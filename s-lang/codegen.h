#ifndef CODEGEN_H
#define CODEGEN_H

#include "token.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class CodeGen
{
public:
    CodeGen();
    void create_project();
    void generate(std::vector<Token> tokens);
    int parse_body(int offset);
    int parse_statement(int offset);

    void parse_function(std::string fname, int offset, std::vector<Token> args);
    std::string parse_args(std::vector<Token> args, bool needColon);
    void build();
    std::string code;

private:
    std::ofstream fout;
    std::vector<Token> tokens;

    std::vector<std::string> listFiles(const std::string& path);
    std::vector<std::string> split(std::string &s, char delim);
    std::string modernize(Token t);
};

#endif // CODEGEN_H
