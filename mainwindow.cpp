#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Electric Charge Station");
    serialPort = new QSerialPort(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveMessage()
{
//    QByteArray dataBA = serialPort->readAll();
//    QString data(dataBA);
//    buffer.append(data);
//    int index = buffer.indexOf(code);
//    if(index != -1){
//       QString message = buffer.mid(0,index);
//       ui->textBrowser->setTextColor(Qt::blue); // Receieved message's color is blue.
//       ui->textBrowser->append(message);
//       buffer.remove(0,index+codeSize);
//    }
}

void MainWindow::init()
{
    sPortInfo.reset(new QSerialPortInfo);

    //add ports to comboBox
    QList <QSerialPortInfo> ports = sPortInfo->availablePorts();
    QStringList stringPorts;
    for(size_t i = 0 ; i < ports.size() ; i++)
        stringPorts.append(ports.at(i).portName());

    ui->cmbBox_port->addItems(stringPorts);

    //add baudRates to comboBox
    QList <qint32> baudRates = sPortInfo->standardBaudRates();
    QStringList stringBaudRates;
    for(size_t i = 3; i < (baudRates.size() - 3); i++)
    {
        if (i < 7 or (i > 7 and i < 10) or i > 10)
            stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->cmbBox_baudRate->addItems(stringBaudRates);

    //add data bits
    QStringList dataBits = {"5","6","7","8"};
    ui->cmbBox_dataBits->addItems(dataBits);

    //add stop bits
    QStringList stopBits = {"1","2"};
    ui->cmbBox_stopBits->addItems(stopBits);

    //add parity
    QStringList parity = {"NoParity","EvenParity","OddParity","SpaceParity","MarkParity"};
    ui->cmbBox_parity->addItems(parity);

    //add flow control
    QStringList flowControl = {"NoFlowControl","HardwareControl","SoftwareControl"};
    ui->cmbBox_flowControl->addItems(flowControl);

    //add select to get data
    QStringList toGetData = {"U and I", "only U", "one time U,I", "one time I"};
    ui->cmbBox_getData->addItems(toGetData);

}


void MainWindow::on_btn_connect_clicked()
{
    serialPort->setPortName(ui->cmbBox_port->currentText());
    serialPort->open(QIODevice::ReadWrite);

    if(!serialPort->isOpen())
    {
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("Problem with opening Serial Port");
    }
    else
    {
        serialPort->setBaudRate(ui->cmbBox_baudRate->currentText().toInt());
        serialPort->setDataBits(static_cast<QSerialPort::DataBits>(ui->cmbBox_dataBits->currentText().toInt()));
        serialPort->setStopBits(static_cast<QSerialPort::StopBits>(ui->cmbBox_stopBits->currentText().toInt()));

        if(ui->cmbBox_parity->currentIndex() == QSerialPort::NoParity)
            serialPort->setParity(QSerialPort::NoParity);
        else
            serialPort->setParity(static_cast<QSerialPort::Parity>(ui->cmbBox_parity->currentIndex() + 1));

        serialPort->setFlowControl(static_cast<QSerialPort::FlowControl>(ui->cmbBox_flowControl->currentIndex()));

        ui->statusbar->showMessage("Connenction enstablished",3000);

        connect(serialPort,&QSerialPort::readyRead,this, &MainWindow::receiveMessage);
    }
}


void MainWindow::on_btn_refreshPorts_clicked()
{
    sPortInfo.reset(new QSerialPortInfo);

    ui->cmbBox_port->clear();
    QList <QSerialPortInfo> ports = sPortInfo.data()->availablePorts();
    QStringList stringPorts;
    for(size_t i = 0 ; i < ports.size() ; i++)
        stringPorts.append(ports.at(i).portName());

    ui->cmbBox_port->addItems(stringPorts);
}


void MainWindow::on_btn_disconnect_clicked()
{
    if(serialPort->isOpen())
        serialPort->close();
}


void MainWindow::on_btn_connectToPC_clicked()
{

    if(!serialPort->isOpen())
        return;
    QString message = m_flagStateFirst ? "C01:1":"C01:0";
    ui->textBrowser->setTextColor(Qt::darkGreen); // Color of message to send is green.
    ui->textBrowser->append(m_flagStateFirst ? "C01:1 - подключить устройство к ПК" : "C01:0 - отключить устройство от ПК");
    serialPort->write(message.toUtf8());
}

