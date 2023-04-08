#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPort>

class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortManager(QObject *parent = nullptr);

    enum ControllerState
    {
        UnknownState = -1,
        Disconnect = 0,
        Connect = 1,
        DataTransfer = 2,
        SingleState = 3,
        WithoutPloter = 4,
        CurrentAndVoltage = 5,
        OnlyVoltage = 6
    };

public slots:
    void receiveSerialMsg();

signals:
    void resourceError(QString error);
    void receiveMsg(const QString &msg);

private slots:
    void handleError(QSerialPort::SerialPortError error);

private:
    void init();
    void changeControllerState(const QString &receiveMsg);
    void changeTransferData();s
    void handlerCommand(const QString &receiveMsg);

private:
    QSerialPort * m_serialPort;
    ControllerState m_controllerState;
//    DataState m_dataState;

};

#endif // SERIALPORTMANAGER_H
