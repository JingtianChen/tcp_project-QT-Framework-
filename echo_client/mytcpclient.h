#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

// Class representing the TCP client.
class MyTcpClient : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpClient(QObject *parent = nullptr);

    // Connects to the specified server.
    void connectToServer(const QString &host, quint16 port);

    // Disconnects from the server.
    void disconnectFromServer();

    // Sends a message to the server.
    void sendMessage(const QString &message);

    // Sets the client ID.
    void setClientId(const QString &id);

signals:
    // Signal emitted when a message is received.
    void messageReceived(const QString &msg);

    // Signal emitted upon successful connection.
    void connected();

    // Signal emitted upon disconnection.
    void disconnected();

    // Signal emitted when an error occurs.
    void errorOccurred(const QString &errorMsg);

private slots:
    // Slot for handling ready-read signal from the socket.
    void onReadyRead();

    // Slot for handling connection signal.
    void onConnected();

    // Slot for handling disconnection signal.
    void onDisconnected();

    // Slot for handling socket error.
    void onErrorOccurred(QTcpSocket::SocketError socketError);

private:
    QTcpSocket *socket;  // Socket for network communication.
    QString clientId;    // Client identifier.
    QString currentHost; // Host address of the server.
};

#endif // MYTCPCLIENT_H
