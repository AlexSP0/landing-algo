#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

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

    int timerId;

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
};

#endif // GAMEWINDOW_H
