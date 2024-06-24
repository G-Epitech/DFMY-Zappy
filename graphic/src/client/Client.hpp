/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Client
*/

#include <string>

#pragma once

class Client {
public:
    /**
     * @brief Construct a new Client object.
     * @details During the construction of the Client object, the connection to the server is established.
     */
    Client();

    /**
     * @brief Destroy the Client object.
     * @details During the destruction of the Client object, the connection to the server is closed.
     */
    ~Client();

    /**
     * @brief Establish a connection to the server.
     * @details This starts the connection and handles the welcome
     * and registering of the client.
     * @param host Hostname or IP address of the server
     * @param port Port of the server
     * @return Success or failure
     */
    bool establishConnection(const std::string &host, int port);

    /**
     * @brief Write data to the server.
     * @param buffer The data to write
     * @param size The size of the data
     * @return The number of bytes written
     */
    ssize_t write(const std::string &buffer, std::size_t size) const;

    /**
     * @brief Write data to the server.
     * @param buffer The data to write
     * @return The number of bytes written
     */
    ssize_t write(const std::string &buffer) const;

    /**
     * @brief Check if the server has data to read.
     * @return True if the server has data to read in the pending buffer, false otherwise.
     */
    [[nodiscard]] bool hasData() const;

    /**
     * @brief Get the next command from the pending buffer.
     * @return The command or an empty string if no command is available.
     */
    std::string getCommandFromPendingBuffer();

    /**
     * @brief Poll the client for new data.
     * @details Call select to check if the server has data to read or if we can write.
     * @param block If true, the function will block until data is available.
     */
    void poll(bool block = false);

    /**
     * @brief Exception class for the Client class.
     */
    class Exception : public std::exception {
    public:
        /**
         * @brief Create a new message queue exception
         * @param message The message
         */
        explicit Exception(std::string message);

        /**
         * @brief Get the exception message
         * @return The exception message
         */
        [[nodiscard]]
        const char *what() const noexcept override;
    
    private:
        /// @brief The exception message
        std::string _message;
    };

private:
    /// @brief The socket used to communicate with the server.
    int _socket;
    /// @brief The buffer used to read data from the server.
    std::string _readBuffer;
    /// @brief The size of the read buffer.
    std::size_t _readBufferSize;
    /// @brief The file descriptor set used for polling.
    fd_set _readSet;

    /**
     * @brief Connect to the server.
     */
    void _connect(const std::string &host, int port);

    /**
     * @brief Disconnect from the server.
     */
    void _disconnect();

    /**
     * @brief Set the socket to non-blocking mode.
     */
    void _setNonBlocking() const;

    /**
     * @brief Read data from the server.
     */
    void _readServer();
};
