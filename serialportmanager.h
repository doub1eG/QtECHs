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
        Disconnect,
        Connect,
        DataTransfer
    };

    enum DataState
    {
        UnknownState,
        SingleState,
        WithoutPloter,
        CurrentAndVoltage,
        OnlyVoltage
    };

public slots:
    void receiveSerialMsg();

signals:
    void resourceError();
    void receiveMsg(QString msg);

private slots:
    void init();
    void changeControllerState(QString receiveMsg);
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort * m_serialPort;
    ControllerState m_controllerState;
    DataState m_dataState;

};

#endif // SERIALPORTMANAGER_H
