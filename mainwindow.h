#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamewindow.h"

#include <QMainWindow>

#include <graphicobjects/testfigure.h>

#include <gameobjects/genecontroller.h>

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

    GameWindow *window;

    GeneController *controller;

    QTimer *timer;

    int currentEpoch;

    int currentGeneration;

private:
    void updateResults(std::vector<GenerationResult> &results);

    void updateStats(int epoch, int generation, int numLander);

    double getEpochTotalFitness(int epoch, std::vector<GenerationResult> &results);

    double getEpochBestFitness(int epoch, std::vector<GenerationResult> &results);

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void tick();
    void onEpochChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
};
#endif // MAINWINDOW_H
