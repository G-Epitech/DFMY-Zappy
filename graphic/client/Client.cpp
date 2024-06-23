/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Client
*/

#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.hpp"

Client::Client(int port, const std::string &host)
    : _socket(-1), _readSet(), _writeSet()
{
    this->_connect(host, port);
    this->pollClient();
    std::string command = this->getCommandFromPendingBuffer();
/*    if (command != "WELCOME") {
        std::cout << command << std::endl;
        throw Client::Exception("Invalid welcome message");
    }*/
    this->write("GRAPHIC\n");
}

Client::~Client()
{
    this->_disconnect();
}

Client::Exception::Exception(std::string message) : _message(message) {}

const char *Client::Exception::what() const noexcept
{
    return this->_message.c_str();
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

std::size_t Client::write(const std::string &buffer, std::size_t size) const
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    ssize_t bytesWritten = ::write(this->_socket, buffer.data(), size);
    if (bytesWritten < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            throw Client::Exception("Error writing to socket");
        }
    }

    return bytesWritten;
}

std::size_t Client::write(const std::string& buffer) const
{
    return this->write(buffer, buffer.size());
}

void Client::_readServer() {
    char buffer[1024] = {0};
    ssize_t bytesRead = 0;

    bytesRead = ::read(this->_socket, buffer, 1024);
    if (bytesRead < 0) {
        if (errno != EAGAIN || errno != EWOULDBLOCK) {
            throw Client::Exception("Error reading from socket");
        }
    } else if (bytesRead == 0) {
        throw Client::Exception("Connection closed");
    }
    this->_pendingBuffer.append(buffer, bytesRead);
    _pendingBytes += bytesRead;
}

bool Client::hasData(bool block) const
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    return this->_pendingBytes > 0;
}

std::string Client::getCommandFromPendingBuffer()
{
    std::size_t pos = this->_pendingBuffer.find('\n');
    std::string command;

    if (pos == std::string::npos) {
        return "";
    }
    command = this->_pendingBuffer.substr(0, pos);
    this->_pendingBuffer = this->_pendingBuffer.substr(pos + 1);
    this->_pendingBytes -= pos + 1;
    return command;
}

void Client::pollClient()
{
    timeval timeout = {0, 0};
    int activity = 0;

    FD_ZERO(&_readSet);
    FD_SET(_socket, &_readSet);
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }
    activity = select(this->_socket + 1, &_readSet, nullptr, nullptr, &timeout);
    if (activity < 0) {
        throw Client::Exception("Error polling client socket");
    }
    if (FD_ISSET(this->_socket, &_readSet)) {
        _readServer();
    }
}
