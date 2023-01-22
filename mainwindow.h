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

public slots:
    void receiveMessage();

private slots:
    void init();

    void changeControllerState(QString receiveMsg);

    void changeTransferData();

    void on_btn_connect_clicked();

    void on_btn_refreshPorts_clicked();

    void on_btn_disconnect_clicked();

    void on_btn_connectToPC_clicked();

    void on_btn_getData_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort * serialPort;
    QScopedPointer <QSerialPortInfo> sPortInfo;

    QString buffer;
    ControllerState state = Disconnect;
};
#endif // MAINWINDOW_H
