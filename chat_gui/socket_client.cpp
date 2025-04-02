// SocketClient.cpp
#include "SocketClient.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

SocketClient::SocketClient(QObject *parent) : QObject(parent), sockfd(-1) {}

SocketClient::~SocketClient() {
    if (sockfd != -1) {
        close(sockfd);
    }
}

bool SocketClient::connectToServer(const QString &ip, int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return false;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.toStdString().c_str(), &server_addr.sin_addr) <= 0) {
        return false;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        return false;
    }

    return true;
}

void SocketClient::sendMessage(const QString &message) {
    if (sockfd != -1) {
        ::sendMessage(sockfd, message.toStdString().c_str());
    }
}

QString SocketClient::receiveMessage() {
    if (sockfd == -1) return "";

    char buffer[1024] = {0};
    ::receiveMessage(sockfd, buffer, sizeof(buffer));
    return QString::fromUtf8(buffer);
}
