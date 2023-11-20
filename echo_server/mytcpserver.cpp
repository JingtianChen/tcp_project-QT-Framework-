#include "mytcpserver.h"
#include <QDateTime>
#include <QRegularExpression>

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer(parent)
{}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (clientSocket->setSocketDescriptor(socketDescriptor)) {
        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    } else {
        delete clientSocket; // Properly handle socket creation failure
    }
}

void MyTcpServer::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    clientSocket->write(data); // Echo back the received data
    emit logMessage(data);     // Log the received data
}

void MyTcpServer::onDisconnected()
{
    emit logMessage("Client disconnected");
    clientSocket->deleteLater(); // Clean up the socket
}
