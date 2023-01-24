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

public slots:
    void init();

    void openVoltagePloter(bool state);

private slots:
    void timerOfPointer();

    void receiveMsgSerialPort();

    int convertToVolt(QString receiveVolt);

private:
    Ui::VoltagePloter *ui;

    QSerialPort * serialPort;
    QTimer *timer;

};

#endif // VOLTAGEPLOTER_H
