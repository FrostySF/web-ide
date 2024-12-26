#include "mainide.h"
#include "ui_mainide.h"
#include "lexer.h"
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
    Lexer l = Lexer(ui->plainTextEdit->toPlainText().toStdString());
    for (Token &a : l.tokens) {
        std::cout << (int)a.tt << " - " << a.desc << std::endl;
    }
    std::cout << "\n\n";
}

MainIDE::~MainIDE()
{
    delete ui;
}

