#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Main window class handling the user interface and interactions.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot for handling the connect button click.
    void on_connectButton_clicked();

    // Slot for handling the disconnect button click.
    void on_disconnectButton_clicked();

    // Slot for handling the send button click.
    void on_sendButton_clicked();

    // Slot for handling received messages.
    void onMessageReceived(const QString &msg);

    // Slot for handling successful connection.
    void onConnected();

    // Slot for handling disconnection.
    void onDisconnected();

    // Slot for handling errors.
    void onErrorOccurred(const QString errorMsg);

private:
    Ui::MainWindow *ui;     // UI pointer for accessing UI elements.
    MyTcpClient *tcpClient; // TCP client for network communication.
};

#endif // MAINWINDOW_H
