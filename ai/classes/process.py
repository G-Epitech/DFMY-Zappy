##
## EPITECH PROJECT, 2024
## zappy
## File description:
## process
##

import time
import multiprocessing
from classes.client import SocketClient
from typing import Callable

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

class SubProcess(multiprocessing.Process):
    def __init__(self, host: str, port: int, name: str, target_func: Callable[[], None]):
        super(SubProcess, self).__init__()
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.client: SocketClient = SocketClient(self.host, self.port)
        self.target_func: Callable[[], None] = target_func

    def run(self):
        time.sleep(4)
        try:
            self.client.connect()
            response = None

            while not response:
                response = self.client.receive()
            print(f"Received: {response}")

            self.client.send(f"{self.name}\n")

            response = None

            time.sleep(2)
            while not response:
                response = self.client.receive()
            print(f"Received: {response}")

            if response == "ko":
                print(f"Process {self.name} finished, server returned KO")
                self.client.close()
                return
        
            self.target_func()

            time.sleep(5)
            
            response = None
            while not response:
                response = self.client.receive()
            print(f"Received: {response}")

            time.sleep(5)

            self.client.close()
        except Exception as e:
            print(f"An error occurred: {str(e)}")
            exit(EXIT_FAILURE)
