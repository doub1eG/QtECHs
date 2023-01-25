#ifndef CURRENTPLOTER_H
#define CURRENTPLOTER_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class CurrentPloter;
}

class CurrentPloter : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentPloter(QSerialPort *ptrSeriaPort = nullptr,QWidget *parent = nullptr);
    ~CurrentPloter();

public slots:
    void openCurrentPloter(bool state);

    void receiveMsgVoltagePloter(QString serialData);

private slots:
    void init();

    int convertToCurr(QString receiveVolt);

private:
    Ui::CurrentPloter *ui;

    QSerialPort * serialPort;

    QVector<double> x,y;
    double sec = 0;
};

#endif // CURRENTPLOTER_H
