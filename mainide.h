#ifndef MAINIDE_H
#define MAINIDE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainIDE; }
QT_END_NAMESPACE

class MainIDE : public QMainWindow
{
    Q_OBJECT

public:
    MainIDE(QWidget *parent = nullptr);
    ~MainIDE();

private:
    Ui::MainIDE *ui;

    void on_build(void);
};
#endif // MAINIDE_H
