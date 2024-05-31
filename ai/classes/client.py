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
        self.host: str = host
        self.port: int = port
        self.sock: socket.socket = None
        self.buffer: str = ""

    def connect(self):
        """
        Connect to the server.
        This method establishes a connection to the server using the specified hostname and port number.
        """
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))
        self.sock.setblocking(False)
        print(f"Connected to {self.host}:{self.port}")

    def send(self, message: str, debug: bool = False) -> None:
        """
        Send a message to the server.

        Args:
            message (str): The message to send, encoded as a string.

        """
        if self.sock:
            try:
                self.sock.sendall(message.encode())
                if debug:
                    print(f"Sent: {message}")
            except socket.error as e:
                if debug:
                    print(f"Error sending message: {e}")
        else:
            if debug:
                print("Connection not established.")

    def receive(self, buffer_size: int = 2048, debug: bool = False) -> str | None:
        """
        Receive a message from the server.

        Args:
            buffer_size (int): The maximum number of bytes to receive. Defaults to 1024.

        Returns:
            str: The received message, decoded from bytes to string.
        """
        pending_data = self.pending_data()
        if pending_data:
            return pending_data

        if self.sock:
            try:
                data = self.sock.recv(buffer_size)
                if data:
                    self.buffer += data.decode()
                    return self.pending_data()
                return None
            except socket.error as e:
                if debug:
                    print(f"Error receiving message: {e}")
                return None
        else:
            if debug:
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
    
    def pending_data(self) -> str | None:
        if "\n" in self.buffer:
            line, self.buffer = self.buffer.split("\n", 1)
            return line
        return None

    def __del__(self):
        if self.sock:
            self.close()

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
