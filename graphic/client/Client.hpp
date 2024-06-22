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
    Client(int port, std::string host = "127.0.0.1");

    /**
     * @brief Destroy the Client object.
     * @details During the destruction of the Client object, the connection to the server is closed.
     */
    ~Client();

    /**
     * @brief Write data to the server.
     * @param buffer The data to write
     * @param size The size of the data
     * @return The number of bytes written
     */
    std::size_t write(const std::string &buffer, std::size_t size);

    /**
     * @brief Write data to the server.
     * @param buffer The data to write
     * @return The number of bytes written
     */
    std::size_t write(const std::string &buffer);

    /**
     * @brief Read data from the server.
     * @param buffer The buffer to store the data
     * @param size The size of the buffer
     * @return The number of bytes read
     */
    std::size_t read(char *buffer, std::size_t size);

    /**
     * @brief Check if the server has data to read.
     * @param block If true, the function will block until data is available.
     * @return True if the server has data to read in the pending buffer, false otherwise.
     */
    bool hasData(bool block = false);

    /**
     * @brief Get the next command from the pending buffer.
     * @return The command or an empty string if no command is available.
     */
    std::string getCommandFromPendingBuffer();

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
    std::string _pendingBuffer;

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
    void _setNonBlocking();
};
