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

private slots:
    void open(bool state);

private:
    Ui::CurrentPloter *ui;

    QSerialPort * serialPort;
};

#endif // CURRENTPLOTER_H
