#include "mainide.h"
#include "ui_mainide.h"
#include "lexer.h"
#include "codegen.h"
#include <iostream>

MainIDE::MainIDE(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainIDE)
{
    ui->setupUi(this);
    connect(ui->build_button, &QAbstractButton::clicked, this, &MainIDE::on_build);
}

std::string findKeyByValue(const std::map<std::string, TokenType>& map, const TokenType& value) {
    for (const auto& pair : map) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return nullptr;
}

void MainIDE::on_build()
{
    //QPushButton *butt = (QPushButton*)sender();
    Lexer l = Lexer(ui->codeEditor->toPlainText().toStdString());
    for (Token &a : l.tokens) {
        std::cout << (int)a.tt << " - " << a.desc << std::endl;
    }
    CodeGen cg = CodeGen();
    cg.create_project();
    cg.generate(l.tokens);
    cg.build();
    std::cout << "\n\n";
}

MainIDE::~MainIDE()
{
    delete ui;
}

