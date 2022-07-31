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
    test.scaleX   = 10;
    test.scaleY   = 10;
    test.rotation = 0;

    this->setAutoFillBackground(true);

    timerId = startTimer(100);
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
    qp.fillRect(e->rect(), QBrush(Qt::white));

    test.rotation = test.rotation + 1;

    test.draw(&qp);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    repaint();
}
