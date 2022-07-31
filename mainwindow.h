#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <graphicobjects/testfigure.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TestFigure test;

    int timerId;

    bool clearFlag;

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};
#endif // MAINWINDOW_H
