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

public slots:
    void receiveMessage();

private slots:
    void init();

    void on_btn_connect_clicked();

    void on_btn_refreshPorts_clicked();

    void on_btn_disconnect_clicked();

    void on_btn_connectToPC_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort * serialPort;
    QScopedPointer <QSerialPortInfo> sPortInfo;

    bool m_flagStateFirst;
    bool m_flagStateSecond;
    bool m_flagStateThird;
};
#endif // MAINWINDOW_H
