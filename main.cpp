#include "mainide.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainIDE w;
    w.show();
    return a.exec();
}
