#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWindow)
    , currentTime(0.0)
    , currentAction(ACTIONS::NOTHING)
{
    ui->setupUi(this);

    resize(600, 600);

    lander = new Lander(width(), height(), *new Vector2D(300, 300), *new Vector2D(100, 0));

    eTimer = new QElapsedTimer();

    eTimer->start();

    timerId = startTimer(10);
}

GameWindow::~GameWindow()
{
    delete eTimer;

    delete lander;

    delete ui;
}

void GameWindow::paintEvent(QPaintEvent *e)
{
    ui->posXLabel->setText(QString::number(lander->posX));
    ui->posYLabel->setText(QString::number(lander->posY));
    ui->rotationLabel->setText(QString::number(lander->rotation));
    ui->velocityXLabel->setText(QString::number(lander->velocity.x));
    ui->velocityYLabel->setText(QString::number(lander->velocity.y));

    QPainter qp(this);

    qp.setRenderHint(QPainter::Antialiasing);
    qp.translate(0, this->height());
    qp.scale(1, -1);

    double time = double(eTimer->restart()) / 1000;

    lander->updateShip(time, currentAction);

    lander->render(&qp);

    currentAction = ACTIONS::NOTHING;

    //    QString time    = QString::number(currentTime);
    //    std::string str = time.toStdString();
    //    qWarning(str.c_str());
}

void GameWindow::timerEvent(QTimerEvent *e)
{
    repaint();
}

void GameWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Left:
        currentAction = ACTIONS::ROTATE_LEFT;
        break;
    case Qt::Key_Right:
        currentAction = ACTIONS::ROTATE_RIGHT;
        break;
    case Qt::Key_Space:
        currentAction = ACTIONS::THRUST;
        break;
    case Qt::Key::Key_Enter:
        currentAction = ACTIONS::ZERO;
        repaint();
    }
}
