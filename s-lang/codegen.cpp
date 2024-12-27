#include "codegen.h"
#include <fstream>

CodeGen::CodeGen()
{

}

std::string startupcode = "";

void CodeGen::create_project()
{
    system("dotnet new console -n SLangApp");
    system("cd SLangApp & del Program.cs & dotnet add package Newtonsoft.Json");
    system("copy Program.cs \"SLangApp/Program.cs\"");
    system("copy Lib.cs SLangApp/Lib.cs");
}

void CodeGen::generate(std::vector<Token> tokens)
{
    //system("cd SLangApp");
    std::ofstream fout("SLangApp/Program.cs", std::ios_base::app);
    fout << "void HandleGET(string source, string path) {\n";
    fout << "switch (source) {\n";
    this->tokens = tokens;
    for (size_t i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        switch (t.tt) {
        case TokenType::WORD:
            {
                Token nt = tokens[i+1];
                if (nt.tt == TokenType::STRING && t.desc == std::string("route")) {
                    fout << "case \"" << nt.desc << "\": {\n";
                    fout << "break;\n}\n";
                    i += 1;
                }
            }
        }
    }
    fout << "}\n}";
    fout.close();
}

void CodeGen::build()
{
    system("cd SLangApp & dotnet build & cls & dotnet run");
}
