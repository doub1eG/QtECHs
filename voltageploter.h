#ifndef VOLTAGEPLOTER_H
#define VOLTAGEPLOTER_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class VoltagePloter;
}

class VoltagePloter : public QWidget
{
    Q_OBJECT

public:
    explicit VoltagePloter(QSerialPort *ptrSeriaPort = nullptr,QWidget *parent = nullptr);
    ~VoltagePloter();

private slots:
    void open(bool state);

private:
    Ui::VoltagePloter *ui;

    QSerialPort * serialPort;
};

#endif // VOLTAGEPLOTER_H
