#include "serialportmanager.h"

//#include <QMessageBox>

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject{parent}
    , m_controllerState(UnknownState)
{

}

void SerialPortManager::receiveSerialMsg()
{
    QByteArray dataBA = m_serialPort->readAll();
    QString msg(dataBA);
//    qInfo() << "msg" << msg;
    msg.chop(2);
    emit receiveMsg(msg);
//    ui->textBrowser->setTextColor(Qt::blue); // Receieved message's color is blue.
//    ui->textBrowser->append("Ответ от МК -> " + msg);

    changeControllerState(msg);
}

void SerialPortManager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        emit resourceError(m_serialPort->errorString());
        if(m_serialPort->isOpen())
            m_serialPort->close();
    }
}

void SerialPortManager::init()
{
    m_serialPort = new QSerialPort(this);
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortManager::receiveSerialMsg);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortManager::handleError);
}

void SerialPortManager::changeControllerState(const QString &receiveMsg)
{
    QString command;
    command.append(receiveMsg[1]).append(receiveMsg[2]);

    switch (command.toInt())
    {
        case 1:
            if(receiveMsg[4] == '1')
            {
                m_controllerState = Connect;
                changeTransferData();
            }
            else if (receiveMsg[4] == '0')
            {
                m_controllerState = Disconnect;
                ui->btn_connectToPC->setEnabled(true);
            }
            break;
        case 2:
            if(receiveMsg[4] == '1')
            {
                m_controllerState = DataTransfer;
                ui->btn_connectToPC->setEnabled(true);
            }
            else if (receiveMsg[4] == '0')
                changeTransferData();
            break;
        case 4:
            convertToVal(receiveMsg);
            break;
    }
}

void SerialPortManager::handlerCommand(const QString &receiveMsg)
{

}

