#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// MainWindow class for the server application.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startServerBtn_clicked();       // Slot for handling start server button click.
    void on_closeServerBtn_clicked();       // Slot for handling close server button click.
    void updateLog(const QString &message); // Slot for updating log messages in the UI.

private:
    Ui::MainWindow *ui;  // UI pointer for accessing UI elements.
    MyTcpServer *server; // Server instance for managing TCP connections.
};

#endif // MAINWINDOW_H
