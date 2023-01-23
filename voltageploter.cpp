#include "voltageploter.h"
#include "ui_voltageploter.h"

VoltagePloter::VoltagePloter(QSerialPort *ptrSeriaPort,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoltagePloter),
    serialPort(ptrSeriaPort)
{
    ui->setupUi(this);
}

VoltagePloter::~VoltagePloter()
{
    delete ui;
}

void VoltagePloter::open(bool state)
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
}
