/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Client
*/

#include <cstring>
#include <utility>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.hpp"

Client::Client()
    : _socket(-1), _readBuffer(), _readBufferSize(0), _readSet() {}

Client::~Client()
{
    this->_disconnect();
}

Client::Exception::Exception(std::string message) : _message(std::move(message)) {}

const char *Client::Exception::what() const noexcept
{
    return this->_message.c_str();
}

bool Client::establishConnection(const std::string &host, int port)
{
    std::string response;
    ssize_t bytesWritten;

    this->_connect(host, port);
    while (true) {
        this->poll(true);
        response = this->getCommandFromPendingBuffer();
        if (response == "WELCOME") {
            break;
        }
        if (response == "ko") {
            return false;
        }
    }
    bytesWritten = this->write("GRAPHIC\n");
    if (bytesWritten == 0) {
        return false;
    }
    this->write("mct\n");
    return true;
}

void Client::_connect(const std::string& host, int port)
{
    this->_disconnect();

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw Client::Exception("Socket creation failed");
    }

    struct sockaddr_in serverAddr = {0};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr) <= 0) {
        close(sockfd);
        throw Client::Exception("Invalid address");
    }

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        close(sockfd);
        throw Client::Exception("Connection failed");
    }

    this->_socket = sockfd;
    this->_setNonBlocking();
}

void Client::_disconnect()
{
    if (this->_socket != -1) {
        close(this->_socket);
        this->_socket = -1;
    }
}

void Client::_setNonBlocking() const
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    int flags = fcntl(this->_socket, F_GETFL, 0);
    if (flags == -1) {
        throw Client::Exception("Error getting flags");
    }

    if (fcntl(this->_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw Client::Exception("Error setting flags");
    }
}

ssize_t Client::write(const std::string &buffer, std::size_t size) const
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    ssize_t bytesWritten = send(this->_socket, buffer.c_str(), size, MSG_DONTWAIT);
    if (bytesWritten < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            throw Client::Exception("Error writing to socket");
        }
    }

    return bytesWritten;
}

ssize_t Client::write(const std::string& buffer) const
{
    return this->write(buffer, buffer.size());
}

void Client::_readServer() {
    char buffer[1024] = {0};
    ssize_t bytesRead;

    bytesRead = recv(this->_socket, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (bytesRead < 0) {
        if (errno != EAGAIN || errno != EWOULDBLOCK) {
            throw Client::Exception("Error reading from socket");
        }
    } else if (bytesRead == 0) {
        throw Client::Exception("Connection closed");
    }
    this->_readBuffer.append(buffer, bytesRead);
    _readBufferSize += bytesRead;
}

bool Client::hasData() const
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    return this->_readBufferSize > 0;
}

std::string Client::getCommandFromPendingBuffer()
{
    std::size_t pos = this->_readBuffer.find('\n');
    std::string command;

    if (pos == std::string::npos) {
        return "";
    }
    command = this->_readBuffer.substr(0, pos);
    this->_readBuffer = this->_readBuffer.substr(pos + 1);
    this->_readBufferSize -= pos + 1;
    return command;
}

void Client::poll(bool block)
{
    timeval timeout = {0, 0};
    timeval *timeoutPtr;
    int activity;

    FD_ZERO(&_readSet);
    FD_SET(_socket, &_readSet);
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }
    timeoutPtr = block ? nullptr : &timeout;
    activity = select(this->_socket + 1, &_readSet, nullptr, nullptr, timeoutPtr);
    if (activity < 0) {
        throw Client::Exception("Error polling client socket");
    }
    if (FD_ISSET(this->_socket, &_readSet)) {
        _readServer();
    }
}
