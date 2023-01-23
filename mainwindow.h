#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum ControllerState
    {
        Disconnect,
        Connect,
        DataTransfer
    };

    enum DataState
    {
        WithoutPloter,
        CurrentAndVoltage,
        OnlyVoltage
    };

signals:
    void openCurrentPloter(bool state);

    void openVoltagePloter(bool state);

public slots:
    void receiveMessage();

private slots:
    void init();

    void changeControllerm_controllerState(QString receiveMsg);

    void changeTransferData();

    void handleError(QSerialPort::SerialPortError error);

    void on_btn_connect_clicked();

    void on_btn_refreshPorts_clicked();

    void on_btn_disconnect_clicked();

    void on_btn_connectToPC_clicked();

    void on_btn_getData_clicked();

    void on_cmbBox_getData_activated(int index);

private:
    Ui::MainWindow *ui;
    QSerialPort * serialPort;
    QScopedPointer <QSerialPortInfo> sPortInfo;

    QString buffer;
    ControllerState controllerState = Disconnect;
    DataState dataState = WithoutPloter;
};
#endif // MAINWINDOW_H
