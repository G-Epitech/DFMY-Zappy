##
## EPITECH PROJECT, 2024
## zappy
## File description:
## socket
##

import socket

class SocketClient:
    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.sock = None

    def connect(self):
        """Establish a connection to the server."""
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))
        self.sock.setblocking(False)
        print(f"Connected to {self.host}:{self.port}")

    def send(self, message: str):
        """Send a message to the server."""
        if self.sock:
            try:
                self.sock.sendall(message.encode())
                print(f"Sent: {message}")
            except socket.error as e:
                print(f"Error sending message: {e}")
        else:
            print("Connection not established.")

    def receive(self, buffer_size: int = 1024):
        """Receive a message from the server."""
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
        """Close the socket connection."""
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
