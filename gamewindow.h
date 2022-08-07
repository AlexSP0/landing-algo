#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QElapsedTimer>
#include <QWidget>

#include "constants.h"
#include "gameobjects/lander.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;

    Lander *lander;

    int timerId;

    QElapsedTimer *eTimer;
    long currentTime;
    ACTIONS currentAction;

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // GAMEWINDOW_H
