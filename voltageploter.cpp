#include "voltageploter.h"
#include "ui_voltageploter.h"
#include "command.h"
#include <QDebug>

VoltagePloter::VoltagePloter(QSerialPort *ptrSeriaPort,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoltagePloter),
    serialPort(ptrSeriaPort)
{
    ui->setupUi(this);
    this->setWindowTitle("Voltage Ploter");
    this->setFixedSize(600,500);
    init();
}

VoltagePloter::~VoltagePloter()
{
    delete ui;
}

void VoltagePloter::init()
{
    this->setFixedSize(600,500);
    this->setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );

    ui->widget->yAxis->setRange(0,1000);
    ui->widget->yAxis->setLabel("Voltage, Volt");
    ui->widget->xAxis->setLabel("Time, Sec");
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setInteraction(QCP::iSelectPlottables, true);
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VoltagePloter::timerOfPointer);
}

void VoltagePloter::openVoltagePloter(bool state)
{
    if(state && this->isHidden())
    {
        y.clear();
        x.clear();
        timer->start(1000);
        this->show();
        return;
    }

    if(!state && this->isVisible())
    {
        timer->stop();
        this->hide();
        return;
    }
}

void VoltagePloter::timerOfPointer()
{
    serialPort->write(QString(READ_DATA).toLocal8Bit());
}

void VoltagePloter::receiveMsgSerialPort()
{
    QByteArray dataBA = serialPort->readAll();
    QString msg(dataBA);
    emit buildCurrentPloter(msg);
    x.push_back(sec);
    y.push_back(double(convertToVolt(msg)));
    ui->widget->graph(0)->addData(x,y);
    ui->widget->rescaleAxes();
    ui->widget->replot();
    ui->widget->update();
    sec++;
}


int VoltagePloter::convertToVolt(QString receiveVolt)
{
    QString voltage;
    voltage.append(receiveVolt[6]).append(receiveVolt[7]).append(receiveVolt[8]).append(receiveVolt[9]);

    int convertVoltage = (voltage.toInt()*1000)/4093;

    return convertVoltage;
}
