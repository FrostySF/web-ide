#include "codegen.h"

CodeGen::CodeGen()
{

}

void CodeGen::create_project()
{
    system("dotnet new console -n SLangApp");
    system("cd SLangApp & del Program.cs & dotnet add package Newtonsoft.Json");
    system("copy Program.cs \"SLangApp/Program.cs\"");
    system("copy Lib.cs SLangApp/Lib.cs");
}


std::vector<std::string> CodeGen::listFiles(const std::string& path) {
    std::vector<std::string> files;

    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (fs::is_regular_file(entry.status())) {
            std::string st = entry.path().string();
            std::string nst = "";
            for (auto &a : st) {
                if (a == '\\')
                    nst += '/';
                else
                    nst += a;
            }
            files.push_back(nst);
        }
    }

    return files;
}

std::vector<std::string> CodeGen::split(std::string &s, char delim) {
    std::vector<std::string> elems = std::vector<std::string>();
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void CodeGen::generate(std::vector<Token> tokens)
{
    fout.open("SLangApp/Program.cs", std::ios_base::app);
    fout << "void HandleGET(Socket clientSocket, string source, string path) {\n"
         << "switch (source) {\n";
    this->tokens = tokens;
    bool isErrorHandlerActive = false;
    for (size_t i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        switch (t.tt) {
        case TokenType::WORD:
            {
                Token nt = tokens[i+1];
                if (nt.tt == TokenType::STRING && t.desc == std::string("route"))
                {
                    fout << "case \"" << nt.desc << "\": {\n";
                    i += parse_body(i + 2);
                }
                else if (nt.tt == TokenType::LBRACE && t.desc == std::string("errhandl"))
                {
                    fout << "default: {\n";
                    i += parse_body(i + 1);
                    isErrorHandlerActive = true;
                }
                else if (nt.tt == TokenType::STRING && t.desc == std::string("staticfolder"))
                {
                    for (std::string &path : listFiles(nt.desc)) {
                        std::string type_a = split(path, '.')[1];
                        std::string type_t = "text/";
                        if (type_a == "json")
                            type_t = "application/";
                        fout << "case \"/" << path << "\": {\n"
                             << "   clientSocket.Send(HttpKit.HttpResp(\"200\", HttpKit.ReadStaticFile(\"" << path << "\"), \"" << type_t << type_a << "\"));\n"
                             << "   break;\n"
                             << "}\n";
                    }
                }
            }
        }
    }
    if (!isErrorHandlerActive) {
        fout << "default: {\n"
             << "   clientSocket.Send(HttpKit.HttpRespError(\"404\", \"error\", \"text/text\"));\n"
             << "   break;\n"
             << "}\n";
    }
    fout << "}\n}";
    fout.close();
}

int CodeGen::parse_body(int offset)
{
    int tmpoffset = 1;
    if (tokens[offset].tt == TokenType::LBRACE) {
        while (tokens[offset + tmpoffset].tt != TokenType::RBRACE) {
            tmpoffset += parse_statement(offset + tmpoffset) + 1;
        }
    }
    fout << "break;\n}\n";
    return tmpoffset;
}

int CodeGen::parse_statement(int offset) {
    int tmpoffset = 0;
    //parse function
    if (tokens[offset + tmpoffset].tt == TokenType::WORD && tokens[offset + tmpoffset + 1].tt == TokenType::LBRACEC) {
        std::string fname = tokens[offset + tmpoffset].desc;
        tmpoffset += 2;
        std::vector<Token> args = std::vector<Token>();
        while (tokens[offset + tmpoffset].tt != TokenType::RBRACEC) {
            if (tokens[offset + tmpoffset].tt == TokenType::COMMA) {
                tmpoffset += 1;
                continue;
            }
            args.push_back(tokens[offset + tmpoffset]);
            tmpoffset += 1;
        }
        parse_function(fname, tmpoffset, args);
    }

    if (tokens[offset + tmpoffset].tt == TokenType::WORD && tokens[offset + tmpoffset + 1].tt == TokenType::EQ) {
        /*
        TODO
        */

        std::string vname = tokens[offset + tmpoffset].desc;
        tmpoffset += 2;
        std::vector<Token> args = std::vector<Token>();
        while (tokens[offset + tmpoffset].tt != TokenType::SEMICOLON) {
            args.push_back(tokens[offset + tmpoffset]);
            tmpoffset += 1;
        }

        fout << "var " << vname << " = " << parse_args(args, false) << ";\n";
    }
    return tmpoffset;
}

void CodeGen::parse_function(std::string fname, int offset, std::vector<Token> args) {
    std::string build = parse_args(args, true);
    if (fname == "log")
    {
        fout << "Console.WriteLine(" << build << ");\n";
    }
    else if (fname == "httpResp")
    {
        fout << "clientSocket.Send(HttpKit.HttpResp(" << build << ", \"text/text\"));\n";
    }
    else if (fname == "httpRespErr")
    {
        fout << "clientSocket.Send(HttpKit.HttpRespError(" << build << ", \"text/text\"));\n";
    }
    else if (fname == "jsonResp")
    {
        fout << "clientSocket.Send(HttpKit.HttpResp(" << build << ", \"application/json\"));\n";
    }
}

std::string CodeGen::modernize(Token t)
{
    std::string build;
    switch (t.tt) {
    case TokenType::STRING:
        {
            build += "\"" + t.desc + "\"";
            break;
        }
    default:
        {
            build += t.desc;
            break;
        }
    }
    return build;
}

std::string CodeGen::parse_args(std::vector<Token> args, bool needColon)
{
    std::string build = "";
    for (int i = 0; i < args.size(); i++) {
        Token t = args[i];
        switch (t.tt) {
        case TokenType::WORD:
            {
                if (t.desc == "jsonify") {
                    i += 1;
                    t = args[i];
                    build += "JsonKit.ConvertToJson(" + modernize(t) + ")";
                } else{
                    build += t.desc;
                }
                break;
            }
        default:
            {
                build += modernize(t);
                break;
            }
        }
        if (needColon && i != args.size() - 1)
            build += ",";
    }
    return build;
}

void CodeGen::build()
{
    utils::crossplatform_exec("@echo off\ncd SLangApp\ndotnet build\ncls\ndotnet run");
}
