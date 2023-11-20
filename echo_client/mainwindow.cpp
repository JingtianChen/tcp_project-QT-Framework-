#include "mainwindow.h"
#include <QDateTime>
#include <QIntValidator>
#include <QMessageBox>
#include "ui_mainwindow.h"

// Constructor for MainWindow. Sets up UI and connects signals to slots.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tcpClient(new MyTcpClient(this))
{
    ui->setupUi(this);

    // Connecting signals from tcpClient to corresponding slots.
    connect(tcpClient, &MyTcpClient::messageReceived, this, &MainWindow::onMessageReceived);
    connect(tcpClient, &MyTcpClient::connected, this, &MainWindow::onConnected);
    connect(tcpClient, &MyTcpClient::disconnected, this, &MainWindow::onDisconnected);
    connect(tcpClient, &MyTcpClient::errorOccurred, this, &MainWindow::onErrorOccurred);

    // Setting a validator for the client ID input to ensure it's a number.
    ui->clientIdLineEdit->setValidator(new QIntValidator(1, 99999, this));
}

// Destructor for MainWindow.
MainWindow::~MainWindow()
{
    delete ui;
}

// Slot implementation for connect button click.
void MainWindow::on_connectButton_clicked()
{
    QString clientId = ui->clientIdLineEdit->text();

    // Checking if client ID is provided.
    if (clientId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Client ID cannot be empty.");
        return;
    }

    // Initiating connection to server with provided client ID.
    tcpClient->setClientId(clientId);
    tcpClient->connectToServer(ui->serverAddressLineEdit->text(), 1502);
}

// Slot implementation for disconnect button click.
void MainWindow::on_disconnectButton_clicked()
{
    tcpClient->disconnectFromServer();
}

// Slot implementation for send button click.
void MainWindow::on_sendButton_clicked()
{
    // Appending the message to the system log before sending.
    ui->systemLogBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss") + ": "
                                 + ui->textToSendTextEdit->text());
    tcpClient->sendMessage(ui->textToSendTextEdit->text());
    ui->textToSendTextEdit->clear();
}

// Slot for handling received messages and displaying them.
void MainWindow::onMessageReceived(const QString &msg)
{
    ui->messageReceivedBrowser->append(msg);
}

// Slot for handling successful connection and logging it.
void MainWindow::onConnected()
{
    ui->systemLogBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss") + ":"
                                 + " Connected to server " + ui->serverAddressLineEdit->text());
}

// Slot for handling disconnection and logging it.
void MainWindow::onDisconnected()
{
    ui->systemLogBrowser->append(QDateTime::currentDateTime().toString("hh:mm:ss") + ":"
                                 + " Disconnected from server " + ui->serverAddressLineEdit->text());
}

// Slot for handling errors and displaying them in the system log.
void MainWindow::onErrorOccurred(const QString errorMsg)
{
    ui->systemLogBrowser->append("Error: " + errorMsg);
}
