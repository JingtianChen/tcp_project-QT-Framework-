#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

// MyTcpServer class representing the TCP server.
class MyTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyTcpServer(QObject *parent = nullptr);

signals:
    void logMessage(const QString &msg); // Signal to log messages.

protected:
    void incomingConnection(qintptr socketDescriptor) override; // Handles new incoming connections.

private slots:
    void onReadyRead();    // Slot to handle ready-read signal from sockets.
    void onDisconnected(); // Slot to handle client disconnection.

private:
    QTcpSocket *clientSocket; // Socket for handling client communication.
};

#endif // MYTCPSERVER_H
