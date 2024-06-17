/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Client
*/

#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.hpp"

Client::Client(int port, std::string host)
{
    this->_socket = -1;
    this->_connect(host, port);

    std::string command = this->getCommand(true);

    if (command != "WELCOME") {
        throw Client::Exception("Invalid welcome message");
    }

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

    struct sockaddr_in serverAddr;
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

void Client::_setNonBlocking()
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

std::size_t Client::write(const std::string &buffer, std::size_t size)
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    ssize_t bytesWritten = send(this->_socket, buffer.data(), size, 0);
    if (bytesWritten < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            throw Client::Exception("Error writing to socket");
        }
    }

    return bytesWritten;
}

std::size_t Client::write(const std::string& buffer)
{
    return this->write(buffer, buffer.size());
}

std::size_t Client::read(std::string& buffer, std::size_t size)
{
    if (this->_socket == -1) {
        throw Client::Exception("Socket not connected");
    }

    buffer.resize(size);

    ssize_t bytesRead = recv(this->_socket, buffer.data(), size, 0);
    if (bytesRead < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        } else {
            throw Client::Exception("Error reading from socket");
        }
    } else if (bytesRead == 0) {
        throw Client::Exception("Connection closed");
    }

    buffer.resize(bytesRead);

    return bytesRead;
}

std::string Client::getCommand(bool block)
{
    std::string command;
    std::size_t size = 1024;
    std::size_t bytesRead = 0;

    bytesRead = this->read(command, size);
    if (block) {
        while (bytesRead == 0) {
            bytesRead = this->read(command, size);
        }
    }
    this->_pendingBuffer += command;

    if (bytesRead == 0) {
        return "";
    }

    return this->_getCommandFromPendingBuffer();
}

std::string Client::_getCommandFromPendingBuffer()
{
    std::string command;
    std::size_t pos = this->_pendingBuffer.find('\n');

    if (pos == std::string::npos) {
        return "";
    }

    command = this->_pendingBuffer.substr(0, pos);
    this->_pendingBuffer = this->_pendingBuffer.substr(pos + 1);

    return command;
}
