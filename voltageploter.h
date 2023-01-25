#ifndef VOLTAGEPLOTER_H
#define VOLTAGEPLOTER_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class VoltagePloter;
}

class VoltagePloter : public QWidget
{
    Q_OBJECT

public:
    explicit VoltagePloter(QSerialPort *ptrSeriaPort = nullptr,QWidget *parent = nullptr);
    ~VoltagePloter();

signals:
    void buildCurrentPloter(QString serialData);

public slots:
    void openVoltagePloter(bool state);

    void receiveMsgSerialPort();

private slots:
    void init();

    void timerOfPointer();

    int convertToVolt(QString receiveVolt);

private:
    Ui::VoltagePloter *ui;

    QSerialPort * serialPort;
    QTimer *timer;

    QVector<double> x,y;
    double sec = 0;
};

#endif // VOLTAGEPLOTER_H
