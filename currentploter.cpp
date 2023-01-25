#include "currentploter.h"
#include "ui_currentploter.h"
#include "command.h"
#include <QDebug>

CurrentPloter::CurrentPloter(QSerialPort *ptrSerialPort,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentPloter),
    serialPort(ptrSerialPort)
{
    ui->setupUi(this);
    this->setWindowTitle("Current Ploter");
    init();
}

CurrentPloter::~CurrentPloter()
{
    delete ui;
}

void CurrentPloter::openCurrentPloter(bool state)
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

void CurrentPloter::receiveMsgVoltagePloter(QString serialData)
{
    QString msg = serialData;
    x.push_back(sec);
    y.push_back(double(convertToCurr(msg)));
    ui->widget->graph(0)->addData(x,y);
    ui->widget->rescaleAxes();
    ui->widget->replot();
    ui->widget->update();
    sec++;
}

void CurrentPloter::init()
{
    this->setFixedSize(600,500);
    this->setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );

    ui->widget->yAxis->setRange(0,1000);
    ui->widget->yAxis->setLabel("Current, Amper");
    ui->widget->xAxis->setLabel("Time, Sec");
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setInteraction(QCP::iSelectPlottables, true);
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

}

int CurrentPloter::convertToCurr(QString receiveCurr)
{
    QString current;
    current.append(receiveCurr[13]).append(receiveCurr[14]).append(receiveCurr[15]).append(receiveCurr[16]);

    int convertCurrent = (current.toInt()*50)/4093;

    return convertCurrent;
}

