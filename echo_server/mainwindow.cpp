#include "mainwindow.h"
#include <QDateTime>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server(new MyTcpServer(this))
{
    ui->setupUi(this);
    connect(server, &MyTcpServer::logMessage, this, &MainWindow::updateLog);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete server; // Clean up server instance
}

void MainWindow::on_startServerBtn_clicked()
{
    if (server->isListening()) {
        ui->msgBrowser->append("Server is already running.");
    } else {
        if (server->listen(QHostAddress::LocalHost, 1502)) {
            ui->msgBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss")
                                   + ": Server started, listening on port 1502.");
        } else {
            ui->msgBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss")
                                   + ": Server failed to start: " + server->errorString());
        }
    }
}

void MainWindow::on_closeServerBtn_clicked()
{
    if (server->isListening()) {
        server->close();
        ui->msgBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss")
                               + ": Server closed");
    } else {
        ui->msgBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss")
                               + ": Server is not running");
    }
}

void MainWindow::updateLog(const QString &message)
{
    ui->msgBrowser->append(message); // Append message to log browser
}
