#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clearFlag(false)
{
    ui->setupUi(this);
    test.posX     = 300;
    test.posY     = 300;
    test.scaleX   = 60;
    test.scaleY   = 20;
    test.rotation = 0;

    timerId = startTimer(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter qp(this);

    //Тут надо почистить окно

    qp.setRenderHint(QPainter::Antialiasing);

    test.rotation = test.rotation + 2;

    test.draw(&qp);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    repaint();
}
