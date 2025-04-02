// SocketClient.h
#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include "client.h"  // Include the C header

class SocketClient : public QObject {
    Q_OBJECT

public:
    explicit SocketClient(QObject *parent = nullptr);
    ~SocketClient();

    bool connectToServer(const QString &ip, int port);
    void sendMessage(const QString &message);
    QString receiveMessage();

private:
    int sockfd;
};

#endif // SOCKETCLIENT_H
