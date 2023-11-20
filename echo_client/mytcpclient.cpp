#include "mytcpclient.h"
#include <QDateTime>

// Constructor for MyTcpClient. Sets up the socket and connects signals to slots.
MyTcpClient::MyTcpClient(QObject *parent)
    : QObject{parent}
    , socket(new QTcpSocket(this))
{
    // Connecting socket signals to respective slots.
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpClient::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &MyTcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpClient::onDisconnected);
    connect(socket,
            QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this,
            &MyTcpClient::onErrorOccurred);
}

// Connects to the server with the specified host and port.
void MyTcpClient::connectToServer(const QString &host, quint16 port)
{
    this->clientId = clientId; // Store the client ID
    this->currentHost = host;
    socket->connectToHost(host, port);
}

// Disconnects from the server.
void MyTcpClient::disconnectFromServer()
{
    socket->disconnectFromHost();
}

// Sends a message to the server.
void MyTcpClient::sendMessage(const QString &message)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QString messageWithId = QDateTime::currentDateTime().toString("hh:mm:ss") + ": " + message
                                + "[ACK:" + clientId + "]";
        socket->write(messageWithId.toUtf8());
        socket->flush(); // Ensure the data is sent immediately
    }
}

// Slot for handling ready-read signal from the socket.
void MyTcpClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    emit messageReceived(QString::fromUtf8(data));
}

// Slot for handling connected signal.
void MyTcpClient::onConnected()
{
    QString idMessage = clientId;
    QString msg = QDateTime::currentDateTime().toString("hh:mm:ss") + ": " + "Client: " + clientId
                  + " Connected to server " + currentHost;
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(msg.toUtf8());
        socket->flush(); // Ensure the data is sent immediately
    }
    emit connected();
}

// Slot for handling disconnected signal.
void MyTcpClient::onDisconnected()
{
    emit disconnected();
}

// Slot for handling socket error.
void MyTcpClient::onErrorOccurred(QTcpSocket::SocketError socketError)
{
    emit errorOccurred(socket->errorString());
}

// Sets the client ID.
void MyTcpClient::setClientId(const QString &id)
{
    clientId = id;
}
