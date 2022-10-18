#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPaintEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableEpochWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Epoch"));
    ui->tableEpochWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("best fitness"));
    ui->tableEpochWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("total fitness"));

    ui->tableGenerationWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Epoch"));
    ui->tableGenerationWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Generation"));
    ui->tableGenerationWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Best fitness"));
    ui->tableGenerationWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Total fitness"));

    connect(ui->tableEpochWidget,
            SIGNAL(currentCellChanged(int, int, int, int)),
            this,
            SLOT(onEpochChanged(int, int, int, int)));

    controller = new GeneController(NUMBER_LANDERS_IN_GENERATION);

    timer = new QTimer();
    timer->setInterval(1);

    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

    currentEpoch      = 0;
    currentGeneration = 0;

    //    window = new GameWindow();
    //    window->show();
}

MainWindow::~MainWindow()
{
    //delete window;

    delete timer;

    delete controller;

    delete ui;
}

void MainWindow::updateResults(std::vector<GenerationResult> &results)
{
    ui->tableEpochWidget->setRowCount(0);

    for (size_t i = 0; i < controller->currentEpoch; i++)
    {
        ui->tableEpochWidget->insertRow(i);

        ui->tableEpochWidget->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(i)));
        ui->tableEpochWidget
            ->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(getEpochBestFitness(i, results))));
        ui->tableEpochWidget
            ->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(getEpochTotalFitness(i, results))));
    }
}

void MainWindow::updateStats(int epoch, int generation, int numLander)
{
    ui->epochNumLabel->setText(QString::number(epoch));
    ui->generationNumLabel->setText(QString::number(generation));
    ui->landerNumLabel->setText(QString::number(numLander));
}

void MainWindow::paintEvent(QPaintEvent *e) {}

void MainWindow::timerEvent(QTimerEvent *)
{
    repaint();
}

void MainWindow::on_startButton_clicked()
{
    timer->start();
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::tick()
{
    if (controller->isBusy == true)
    {
        if (currentEpoch != controller->currentEpoch
            || currentGeneration != controller->currentGeneration)
        {
            updateResults(controller->results);
        }

        updateResults(controller->results);

        controller->trainNext();
        updateStats(controller->currentEpoch,
                    controller->currentGeneration,
                    controller->currentLander);
    }
    else
    {
        on_stopButton_clicked();
    }
}

void MainWindow::onEpochChanged(int currentRow,
                                int currentColumn,
                                int previousRow,
                                int previousColumn)
{
    //qWarning("Select!");
    std::vector<GenerationResult> generationOfEpoch;
    for (size_t i = 0; i < controller->results.size(); i++)
    {
        if (controller->results[i].epoch == currentRow)
        {
            generationOfEpoch.push_back(controller->results[i]);
        }
    }

    ui->tableGenerationWidget->setRowCount(0);

    for (size_t i = 0; i < generationOfEpoch.size(); i++)
    {
        ui->tableGenerationWidget->insertRow(i);

        ui->tableGenerationWidget
            ->setItem(i, 0, new QTableWidgetItem(tr("%1").arg(generationOfEpoch[i].epoch)));
        ui->tableGenerationWidget
            ->setItem(i, 1, new QTableWidgetItem(tr("%1").arg(generationOfEpoch[i].generation)));
        ui->tableGenerationWidget
            ->setItem(i, 2, new QTableWidgetItem(tr("%1").arg(generationOfEpoch[i].bestFitness)));
        ui->tableGenerationWidget
            ->setItem(i, 3, new QTableWidgetItem(tr("%1").arg(generationOfEpoch[i].totalFitness)));
    }
}

double MainWindow::getEpochTotalFitness(int epoch, std::vector<GenerationResult> &results)
{
    double total = 0;

    for (size_t i = 0; i < results.size(); i++)
    {
        if (results[i].epoch == epoch)
        {
            total = total + results[i].totalFitness;
        }
    }

    return total;
}

double MainWindow::getEpochBestFitness(int epoch, std::vector<GenerationResult> &results)
{
    double bestFitness = 0;

    for (size_t i = 0; i < results.size(); i++)
    {
        if (results[i].epoch == epoch)
        {
            if (bestFitness < results[i].bestFitness)
            {
                bestFitness = results[i].bestFitness;
            }
        }
    }

    return bestFitness;
}
