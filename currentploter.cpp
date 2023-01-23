#include "currentploter.h"
#include "ui_currentploter.h"
#include <QDebug>

CurrentPloter::CurrentPloter(QSerialPort *ptrSerialPort,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentPloter),
    serialPort(ptrSerialPort)
{
    ui->setupUi(this);
}

CurrentPloter::~CurrentPloter()
{
    delete ui;
}

void CurrentPloter::open(bool state)
{
    if(state && this->isHidden())
    {
        this->show();
        return;
    }

    if(!state && this->isVisible())
    {
        this->hide();
        return;
    }
    qDebug() << "already hidden or Visible";
}
