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
from classes.hamster import Hamster

EXIT_SUCCESS = 0
EXIT_FAILURE = 84

class SubProcess(multiprocessing.Process):
    def __init__(self, host: str, port: int, name: str, add_subprocess: Callable[[], None], ID: int):
        super(SubProcess, self).__init__()
        self.host: str = host
        self.port: int = port
        self.name: str = name
        self.client: SocketClient = SocketClient(self.host, self.port)
        self.add_subprocess: Callable[[], None] = add_subprocess
        self.ID: int = ID

    def run(self):
        time.sleep(4)
        self.debug(f"Starting player in team {self.name}")
        try:
            self.client.connect()

            response = None
            while not response:
                response = self.client.receive()
            
            if response != "WELCOME":
                self.debug(f"Server did not send WELCOME, received: {response}")
                self.client.close()
                return

            self.client.send(f"{self.name}\n")

            response = None
            while not response:
                response = self.client.receive()

            if response == "ko":
                self.debug(f"Server did not accept me, received: {response}")
                self.client.close()
                return

            available_clients = int(response)

            if available_clients > 0:
                self.add_subprocess()

            response = None
            while not response:
                response = self.client.receive()

            map_size = tuple(map(int, response.split()))

            hamster = Hamster(self.client, self.name, map_size, self.add_subprocess)

            hamster.run()

            time.sleep(6)

            self.client.close()
        except Exception as e:
            self.debug(f"An error occured: {e}")
            exit(EXIT_FAILURE)
        self.debug(f"I'm leaving the team")

    def debug(self, string: str):
        print(f"[{time.strftime('%H:%M:%S')}] Process {self.ID}: {string}")