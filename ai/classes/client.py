##
## EPITECH PROJECT, 2024
## zappy
## File description:
## socket
##

import socket

class SocketClient:
    """
    A class representing a socket client.

    The SocketClient class is used to establish a connection to a server using TCP/IP sockets.
    It provides methods to connect to the server, send messages, receive messages, and close the connection.

    Args:
        host (str): The hostname or IP address of the server.
        port (int): The port number to connect to on the server.

    Attributes:
        host (str): The hostname or IP address of the server.
        port (int): The port number to connect to on the server.
        sock (socket.socket): The socket object representing the connection to the server.

    """

    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.sock = None

    def connect(self):
        """
        Connect to the server.
        This method establishes a connection to the server using the specified hostname and port number.
        """
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))
        self.sock.setblocking(False)
        print(f"Connected to {self.host}:{self.port}")

    def send(self, message: str):
        """
        Send a message to the server.

        Args:
            message (str): The message to send, encoded as a string.

        """
        if self.sock:
            try:
                self.sock.sendall(message.encode())
                print(f"Sent: {message}")
            except socket.error as e:
                print(f"Error sending message: {e}")
        else:
            print("Connection not established.")

    def receive(self, buffer_size: int = 1024) -> str:
        """
        Receive a message from the server.

        Args:
            buffer_size (int): The maximum number of bytes to receive. Defaults to 1024.

        Returns:
            str: The received message, decoded from bytes to string.
        """

        if self.sock:
            try:
                response = self.sock.recv(buffer_size)
                return response.decode()
            except socket.error as e:
                print(f"Error receiving message: {e}")
                return None
        else:
            print("Connection not established.")
            return None

    def close(self):
        """
        Close the connection to the server.
        This method closes the connection to the server and cleans up the socket object.
        """
        if self.sock:
            try:
                self.sock.close()
                self.sock = None
                print("Connection closed.")
            except socket.error as e:
                print(f"Error closing connection: {e}")
        else:
            print("Connection not established.")

# Example usage
if __name__ == "__main__":
    client = SocketClient('127.0.0.1', 3001)
    client.connect()
    response = client.receive()
    print(f"Received: {response}")
    client.send("team1\n")
    response = client.receive()
    print(f"Received: {response}")
    client.close()
