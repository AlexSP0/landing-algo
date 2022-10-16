#include "mainwindow.h"

#include <QApplication>

#include <neuronet/sneuralnet.h>

int main(int argc, char *argv[])
{
    neuro::SNeuralNet net(2, 2, 3, 10, 10);

    std::vector<double> we;
    for (size_t i = 0; i < 956; i++)
    {
        we.push_back(1.001);
    }

    net.putWeights(we);

    std::vector<double> in;
    in.push_back(0.5);
    in.push_back(-0.7);
    net.Update(in);

    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
