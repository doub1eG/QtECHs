#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
//#include <QSharedPointer>
#include <currentploter.h>
#include <voltageploter.h>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    enum ControllerState
    {
        Disconnect,
        Connect,
        DataTransfer
    };

    enum DataState
    {
        SingleState,
        WithoutPloter,
        CurrentAndVoltage,
        OnlyVoltage
    };

signals:
    void openCurrentPloter(bool state);

    void openVoltagePloter(bool state);

private slots:
    void init();

    void changeControllerm_controllerState(QString receiveMsg);

    void changeTransferData();

    void handleError(QSerialPort::SerialPortError error);

    void convertToVal(QString receiveData);

    void receiveMessage();

    void closeEvent(QCloseEvent *event) override;

    void on_btn_connect_clicked();

    void on_btn_refreshPorts_clicked();

    void on_btn_disconnect_clicked();

    void on_btn_connectToPC_clicked();

    void on_btn_getData_clicked();

    void on_cmbBox_getData_activated(int index);

private:
    Ui::MainWindow *ui;
    QSerialPort * serialPort;
    CurrentPloter * currentPloter;
    VoltagePloter * voltagePloter;
    QScopedPointer <QSerialPortInfo> sPortInfo;

    QString buffer;
    ControllerState controllerState = Disconnect;
    DataState dataState = WithoutPloter;
};
#endif // MAINWINDOW_H
