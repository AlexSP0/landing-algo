#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window = new GameWindow();

    window->show();
}

MainWindow::~MainWindow()
{
    delete window;

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e) {}

void MainWindow::timerEvent(QTimerEvent *)
{
    repaint();
}
